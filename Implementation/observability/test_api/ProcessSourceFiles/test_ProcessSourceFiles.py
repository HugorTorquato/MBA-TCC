import logging
import requests
from configs.logging_config import configure_logging

from configs.variables import *

# Configure logging for tests
configure_logging()
logger = logging.getLogger("[ProcessSourceFilesTests]")

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

def test_v1_downloadFilesInUrl_EmptyProjectFoldeStructure():

    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure"
    }

    response = requests.post(f"{BASE_URL}/api/v1/downloadFilesInUrl", json=input_json)

    assert response.status_code == 200  

    data = response.json()
    assert isinstance(data, dict), "Expected a dictionary response"

    expected_order = [
        ("File1.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/File1.cpp", "Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/File1.cpp"),
        ("File1.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder1/File1.cpp", "Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder1/File1.cpp"),
        ("File1.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2/File1.cpp", "Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2/File1.cpp"),
        ("File2.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2/File2.cpp", "Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2/File2.cpp"),
        ("Folder1:Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder1", "Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder1"),
        ("Folder2:Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2", "Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2"),
        ("root:", "")
    ]

    for idx, (name, path) in enumerate(data.items()):
        
        # Assert that the current name and path match the expected values
        expected_name, expected_path = expected_order[idx]
        assert name == expected_name, f"Name - Expected {expected_name}, but got {name} at position {idx}"
        assert path == expected_path, f"Path - Expected {expected_path}, but got {path} at position {idx}"

        # Additional checks to ensure types are correct
        assert isinstance(name, str), f"Expected string as filename, got {type(name)}"
        assert isinstance(path, str), f"Expected string as path, got {type(path)}"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200 

def test_v1_retreveSourceFileContent_DownloadAndReadSourceFileWithOneComment():

    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Scanner/Implementation/observability/source_code_for_testing/ProcessSourceFiles/SimpleSorceExampleForReaderTests"
    }

    response = requests.post(f"{BASE_URL}/api/v1/downloadFilesInUrl", json=input_json)
    data = response.json()
    
    # Response is valid JSON and not empty
    assert response.status_code == 200  

    expected_order = [
        ("main.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/SimpleSorceExampleForReaderTests/main.cpp","Implementation/observability/source_code_for_testing/ProcessSourceFiles/SimpleSorceExampleForReaderTests/main.cpp"),
        ("root:", "")
    ]

    for idx, (name, path) in enumerate(data.items()):
        
        # Assert that the current name and path match the expected values
        expected_name, expected_path = expected_order[idx]
        assert name == expected_name, f"Name - Expected {expected_name}, but got {name} at position {idx}"
        assert path == expected_path, f"Path - Expected {expected_path}, but got {path} at position {idx}"

        # Additional checks to ensure types are correct
        assert isinstance(name, str), f"Expected string as filename, got {type(name)}"
        assert isinstance(path, str), f"Expected string as path, got {type(path)}"

    response = requests.post(f"{BASE_URL}/api/v1/downloadAndRetreveSourceFileContent", json=input_json)
    data = response.json()
    assert response.status_code == 200  

