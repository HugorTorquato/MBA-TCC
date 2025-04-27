import requests

from configs.variables import *

def test_v1_listFilesInUrl_SimpleMainFile():

    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/4---API-Observability-and-Tests/Implementation/observability/source_code_for_testing/ProcessSourceFiles/SimpleMainFile"
    }

    response = requests.post(f"{BASE_URL}/api/v1/listFilesInUrl", json=input_json)
    data = response.json()
    
    # Response is valid JSON and not empty
    assert response.status_code == 200  
    assert isinstance(data, list)
    assert len(data) > 0

    for item in data:
        assert item["name"] == "main.cpp", f"Expected name 'main.cpp', but got {item['name']}"
        assert item["type"] == "file", f"Expected a file, but got {item['type']}"

def test_v1_listFilesInUrl_EmptyProjectFoldeStructure():

    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure"
    }

    response = requests.post(f"{BASE_URL}/api/v1/downloadFilesInUrl", json=input_json)
    data = response.json()

    assert response.status_code == 200  
    assert isinstance(data, list)
    assert len(data) > 0

    # for item in data:
    #     assert item["type"] in {"file", "dir"}, f"Expected name (file, folder), but got {item['type']}"