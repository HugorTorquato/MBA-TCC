import pytest
from pathlib import Path
from test_api.ProcessSourceFiles.util import dump_json_result, createDOTRepresentation

@pytest.fixture(autouse=True)
def auto_dump_after_test(request):
    """
    Autouse fixture: after every test, if `request.node.last_response` is set,
    dump it as JSON into <same_folder_as_test>/api_test_results/.
    """
    yield
    last = getattr(request.node, "last_response", None)
    if last is not None:
        test_file = Path(str(request.node.fspath))      # the test file path
        output_dir = test_file.parent / "api_test_results"
        output_dot_dir = test_file.parent / "Dots"
        test_name = request.node.name

        try:
            path = dump_json_result(
                last,
                test_name=test_name,
                target_folder=output_dir
            )
            print(f"[auto_dump_after_test] dumped JSON for {test_name} -> {path}")
            createDOTRepresentation(
                last,
                test_name=test_name,
                target_folder=output_dot_dir
            )
            print(f"[auto_dump_after_test] dumped DOT for {test_name} -> {path}")
        except Exception as exc:
            print(f"[auto_dump_after_test] failed to dump for {test_name}: {exc}")
