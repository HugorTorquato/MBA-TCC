import json
import os
from pathlib import Path
from datetime import datetime
from graphviz import Digraph

def ensure_dir(path: Path):
    path.mkdir(parents=True, exist_ok=True)

def dump_json_result(
    data,
    test_name: str,
    target_folder: str | Path,
    filename_suffix: str | None = None,
    pretty: bool = True,
    keep_last: int = 3
) -> Path:
    base_folder = Path(target_folder).expanduser().resolve()
    ensure_dir(base_folder)

    ts = datetime.utcnow().strftime("%Y%m%dT%H%M%SZ")
    pid = os.getpid()
    suffix = f"_{filename_suffix}" if filename_suffix else ""
    filename = f"{test_name}_{ts}_{pid}{suffix}.json"
    path = base_folder / filename

    # Save JSON
    with open(path, "w", encoding="utf-8") as f:
        if pretty:
            json.dump(data, f, indent=2, ensure_ascii=False)
        else:
            json.dump(data, f, ensure_ascii=False)

    # Cleanup old files, keep only last N
    all_files = sorted(
        base_folder.glob(f"{test_name}_*.json"),
        key=lambda p: p.stat().st_mtime,
        reverse=True
    )
    for old_file in all_files[keep_last:]:
        try:
            old_file.unlink()
            print(f"[dump_json_result] deleted old dump: {old_file}")
        except Exception as e:
            print(f"[dump_json_result] failed to delete {old_file}: {e}")

    return path


def createDOTRepresentation(
    classesJson,
    test_name: str,
    target_folder: str | Path,
    filename_suffix: str | None = None
) -> None:
    """
    Cria uma representação DOT de um diagrama de classes a partir de uma estrutura JSON.
    """

    base_folder = Path(target_folder).expanduser().resolve()
    ensure_dir(base_folder)

    ts = datetime.utcnow().strftime("%Y%m%dT%H%M%SZ")
    pid = os.getpid()
    suffix = f"_{filename_suffix}" if filename_suffix else "_ClassDiagram"
    filename = f"{test_name}_{ts}_{pid}{suffix}"
    path = base_folder / filename

    dot = Digraph("ClassDiagram", format="png")

    # Configurações visuais globais
    dot.attr(rankdir="BT")  # mostra heranças de cima para baixo
    dot.attr("node", shape="box", style="filled", color="lightgrey")

    # Adicionar nós para cada classe
    for cls in classesJson:
        dot.node(cls["className"])

    # Adicionar arestas de herança
    for cls in classesJson:
        for inh in cls["inherency"]:
            base_class = inh["second"]["lexeme"]
            relation_type = inh["first"]["lexeme"]  # public/private/protected

            # Diferenciar estilos
            style = "solid"
            color = "black"
            if relation_type == "private":
                style = "dashed"
                color = "red"
            elif relation_type == "protected":
                style = "dotted"
                color = "blue"

            dot.edge(cls["className"], base_class, label=relation_type,
                     style=style, color=color)

    # Exportar
    dot.attr(rankdir="TB")
    dot.attr("node", shape="box", style="filled", color="lightgrey", fontsize="8") # Fonte menor
    dot.attr("edge", fontsize="8") # Fonte menor na aresta

    dot.render(f"{path}", format="pdf", cleanup=True)
    dot.render(f"{path}", format="png", cleanup=True)
    dot.save(f"{path}.dot")

    print(f"Arquivos gerados: {path}.png e {path}.dot")
