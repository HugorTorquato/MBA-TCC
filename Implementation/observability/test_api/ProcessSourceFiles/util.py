import json
import os
from pathlib import Path
from datetime import datetime

def ensure_dir(path: Path):
    path.mkdir(parents=True, exist_ok=True)

def dump_json_result(
    data,
    test_name: str,
    target_folder: str | Path,
    filename_suffix: str | None = None,
    pretty: bool = True
) -> Path:
    """
    Dump JSON-like `data` to <target_folder>/<test_name>_<timestamp>_<pid>.json
    """
    base_folder = Path(target_folder).expanduser().resolve()
    ensure_dir(base_folder)

    ts = datetime.utcnow().strftime("%Y%m%dT%H%M%SZ")
    pid = os.getpid()
    suffix = f"_{filename_suffix}" if filename_suffix else ""
    filename = f"{test_name}_{ts}_{pid}{suffix}.json"
    path = base_folder / filename

    with open(path, "w", encoding="utf-8") as f:
        if pretty:
            json.dump(data, f, indent=2, ensure_ascii=False)
        else:
            json.dump(data, f, ensure_ascii=False)

    return path
