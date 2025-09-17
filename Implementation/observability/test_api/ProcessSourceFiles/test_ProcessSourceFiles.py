import logging
import requests
from configs.logging_config import configure_logging
from collections import Counter

from configs.variables import *

# Configure logging for tests
configure_logging()
logger = logging.getLogger("[ProcessSourceFilesTests]")

def test_v1_listFilesInUrl_SimpleMainFile(request):

    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/4---API-Observability-and-Tests/Implementation/observability/source_code_for_testing/ProcessSourceFiles/SimpleMainFile"
    }

    response = requests.post(f"{BASE_URL}/api/v1/listFilesInUrl", json=input_json)
    data = response.json()
    # register so fixture can dump automatically
    request.node.last_response = data
    
    # Response is valid JSON and not empty
    assert response.status_code == 200  
    assert isinstance(data, list)
    assert len(data) > 0

    for item in data:
        assert item["name"] == "main.cpp", f"Expected name 'main.cpp', but got {item['name']}"
        assert item["type"] == "file", f"Expected a file, but got {item['type']}"

def test_v1_downloadFilesInUrl_EmptyProjectFoldeStructure(request):

    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure"
    }

    response = requests.post(f"{BASE_URL}/api/v1/downloadFilesInUrl", json=input_json)

    assert response.status_code == 200  

    data = response.json()
    assert isinstance(data, dict), "Expected a dictionary response"
    # register so fixture can dump automatically
    request.node.last_response = data

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

def test_v1_retreveSourceFileContent_DownloadAndReadSourceFileWithOneComment(request):

    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Scanner/Implementation/observability/source_code_for_testing/ProcessSourceFiles/SimpleSorceExampleForReaderTests"
    }

    response = requests.post(f"{BASE_URL}/api/v1/downloadFilesInUrl", json=input_json)
    data = response.json()
    
    # Response is valid JSON and not empty
    assert response.status_code == 200  

    # register so fixture can dump automatically
    request.node.last_response = data

    expected_order = [
        ("main.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/SimpleSorceExampleForReaderTests/main.cpp",
            "Implementation/observability/source_code_for_testing/ProcessSourceFiles/SimpleSorceExampleForReaderTests/main.cpp"),
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

    # register so fixture can dump automatically
    request.node.last_response = data

    expected_result = [
        ("main.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/SimpleSorceExampleForReaderTests/main.cpp","// First Example only with text content that must be displayed in the source reader as comment")
    ]

    for idx, (name, content) in enumerate(data.items()):
        expected_name, expected_content = expected_result[idx]
        assert name == expected_name, f"Name - Expected {expected_name}, but got {name} at position {idx}"
        assert content == expected_content, f"Content - Expected {expected_content}, but got {content} at position {idx}"
        assert isinstance(name, str), f"Expected string as filename, got {type(name)}"
        assert isinstance(content, str), f"Expected string as content, got {type(content)}"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200 

def test_v1_retreveSourceFileContent_DownloadAndReadSourceFileWithOneComment_2Files(request):

    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Scanner/Implementation/observability/source_code_for_testing/ProcessSourceFiles/TwoFileSourceCode"
    }

    response = requests.post(f"{BASE_URL}/api/v1/downloadAndRetreveSourceFileContent", json=input_json)
    data = response.json()
    assert response.status_code == 200  

    # register so fixture can dump automatically
    request.node.last_response = data

    expected_result = [
        ("classDef.h:Implementation/observability/source_code_for_testing/ProcessSourceFiles/TwoFileSourceCode/classDef.h",
        "#pragma once\n\nclass hugo {\n\n};"),
        ("main.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/TwoFileSourceCode/main.cpp",
        "#include \"classDef.h\"")
    ]

    for idx, (name, content) in enumerate(data.items()):
        expected_name, expected_content = expected_result[idx]
        assert name == expected_name, f"Name - Expected {expected_name}, but got {name} at position {idx}"
        assert content == expected_content, f"Content - Expected {expected_content}, but got {content} at position {idx}"
        assert isinstance(name, str), f"Expected string as filename, got {type(name)}"
        assert isinstance(content, str), f"Expected string as content, got {type(content)}"


def test_v1_processSourceCode_ClassWithNoInherency(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/TwoFileSourceCode"
    }

    logger.info(f"test_v1_processSourceCode_ClassWithNoInherency")
    logger.info(f"Input JSON: {input_json}")

    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    logger.info(f"Response: {response.status_code} - {response.text}")
    data = response.json()
    assert response.status_code == 200  

    # register so fixture can dump automatically
    request.node.last_response = data

    # I need to clear the container, it's growing 2 by 2. Addng duplicated classes
    # expected result = [{"className":"hugo","inherency":[]},{"className":"hugo","inherency":[]},{"className":"hugo","inherency":[]},{"className":"hugo","inherency":[]}]
    expected_result = [
        {"className":"C1","inherency":[]}
    ]

    #expect that data contains expected_result
    for expected in expected_result:
        assert expected in data, f"Expected {expected} to be in response data"

    # count the number of occurrences of each className in data
    class_name_counts = Counter(item["className"] for item in data)

    logger.info(f"Class name counts: {class_name_counts}")

    # # Ensure each className appears only once ( TODO )
    # for class_name, count in class_name_counts.items():
    #     assert count == 1, f"Class name {class_name} appears {count} times, expected only once"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200 

def test_v1_processSourceCode_ClassWithInherency(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/TwoFileSourceCodeWithInherency"
    }

    logger.info(f"test_v1_processSourceCode_ClassWithInherency")
    logger.info(f"Input JSON: {input_json}")

    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    logger.info(f"Response: {response.status_code} - {response.text}")
    data = response.json()
    assert response.status_code == 200  

    # register so fixture can dump automatically
    request.node.last_response = data

    # I need to clear the container, it's growing 2 by 2. Addng duplicated classes
    # classesJson: [{"className":"hugo","inherency":[]},{"className":"hugo","inherency":[]},{"className":"hugo","inherency":[]},{"className":"Tayna","inherency":[]},{"className":"Derived","inherency":[{"first":{"lexeme":"public","type":"PUBLIC"},"second":{"lexeme":"hugo","type":"IDENTIFIER"}},{"first":{"lexeme":"public","type":"PUBLIC"},"second":{"lexeme":"Tayna","type":"IDENTIFIER"}}]},{"className":"hugo","inherency":[]},{"className":"Tayna","inherency":[]},{"className":"Derived","inherency":[{"first":{"lexeme":"public","type":"PUBLIC"},"second":{"lexeme":"hugo","type":"IDENTIFIER"}},{"first":{"lexeme":"public","type":"PUBLIC"},"second":{"lexeme":"Tayna","type":"IDENTIFIER"}}]},{"className":"hugo","inherency":[]},{"className":"hugo","inherency":[]},{"className":"hugo","inherency":[]},{"className":"Tayna","inherency":[]},{"className":"Derived","inherency":[{"first":{"lexeme":"public","type":"PUBLIC"},"second":{"lexeme":"hugo","type":"IDENTIFIER"}},{"first":{"lexeme":"public","type":"PUBLIC"},"second":{"lexeme":"Tayna","type":"IDENTIFIER"}}]},{"className":"hugo","inherency":[]},{"className":"Tayna","inherency":[]},{"className":"Derived","inherency":[{"first":{"lexeme":"public","type":"PUBLIC"},"second":{"lexeme":"hugo","type":"IDENTIFIER"}},{"first":{"lexeme":"public","type":"PUBLIC"},"second":{"lexeme":"Tayna","type":"IDENTIFIER"}}]}]

    expected_result = [
        {"className":"ble","inherency":[]},
        {"className":"bla","inherency":[]},
        {"className":"blu","inherency":[{"first":{"lexeme":"public","type":"PUBLIC"},"second":{"lexeme":"ble","type":"IDENTIFIER"}},{"first":{"lexeme":"private","type":"PRIVATE"},"second":{"lexeme":"bla","type":"IDENTIFIER"}}]}
    ]

    #expect that data contains expected_result
    for expected in expected_result:
        assert expected in data, f"Expected {expected} to be in response data"

    # count the number of occurrences of each className in data
    class_name_counts = Counter(item["className"] for item in data)

    logger.info(f"Class name counts: {class_name_counts}")

    # # Ensure each className appears only once ( TODO )
    # for class_name, count in class_name_counts.items():
    #     assert count == 1, f"Class name {class_name} appears {count} times, expected only once"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200 

def test_v1_processSourceCode_ClassWithInherencyDifferentFiles(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/ThreeFileSourceCodeWithInherency"
    }

    logger.info(f"test_v1_processSourceCode_ClassWithInherencyDifferentFiles")
    logger.info(f"Input JSON: {input_json}")

    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    logger.info(f"Response: {response.status_code} - {response.text}")
    data = response.json()
    assert response.status_code == 200  

    # register so fixture can dump automatically
    request.node.last_response = data

    expected_result = [
        {"className":"ble","inherency":[]},
        {"className":"bla","inherency":[{"first":{"lexeme":"public","type":"PUBLIC"},"second":{"lexeme":"ble","type":"IDENTIFIER"}}]}
    ]

    #expect that data contains expected_result
    for expected in expected_result:
        assert expected in data, f"Expected {expected} to be in response data"

    # count the number of occurrences of each className in data
    class_name_counts = Counter(item["className"] for item in data)

    logger.info(f"Class name counts: {class_name_counts}")

    # # Ensure each className appears only once ( TODO )
    # for class_name, count in class_name_counts.items():
    #     assert count == 1, f"Class name {class_name} appears {count} times, expected only once"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200

def test_v1_processSourceCode_ClassWithMultipleInherency(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/ClassWithMultipleInherency"
    }

    logger.info("test_v1_processSourceCode_ClassWithMultipleInherency")
    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    data = response.json()
    assert response.status_code == 200

    request.node.last_response = data  # register for JSON dump

    expected_result = [
        {"className": "A", "inherency": []},
        {"className": "B", "inherency": []},
        {"className": "C", "inherency": [
            {"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "A", "type": "IDENTIFIER"}},
            {"first": {"lexeme": "private", "type": "PRIVATE"}, "second": {"lexeme": "B", "type": "IDENTIFIER"}},
        ]},
    ]

    for expected in expected_result:
        assert expected in data, f"Expected {expected} in response"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200

def test_v1_processSourceCode_ClassWithChain(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/chain"
    }

    logger.info("test_v1_processSourceCode_ClassWithChain")
    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    data = response.json()
    assert response.status_code == 200

    request.node.last_response = data  # register for JSON dump

    expected_result = [
        {"className": "A", "inherency": []},
        {"className": "B", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "A", "type": "IDENTIFIER"}}]},
        {"className": "C", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "B", "type": "IDENTIFIER"}}]},
        {"className": "D", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "C", "type": "IDENTIFIER"}}]},
    ]

    for expected in expected_result:
        assert expected in data, f"Expected {expected} in response"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200

def test_v1_processSourceCode_ClassWithDiamond(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/diamond"
    }

    logger.info("test_v1_processSourceCode_ClassWithDiamond")
    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    data = response.json()
    assert response.status_code == 200

    request.node.last_response = data  # register for JSON dump

    expected_result = [
        {"className": "A", "inherency": []},
        {"className": "B", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "A", "type": "IDENTIFIER"}}]},
        {"className": "C", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "A", "type": "IDENTIFIER"}}]},
        {"className": "D", "inherency": [
            {"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "B", "type": "IDENTIFIER"}},
            {"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "C", "type": "IDENTIFIER"}}
        ]}
    ]

    for expected in expected_result:
        assert expected in data, f"Expected {expected} in response"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200

def test_v1_processSourceCode_ClassWithForward_and_external(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/forward_and_external"
    }

    logger.info("test_v1_processSourceCode_ClassWithForward_and_external")
    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    data = response.json()
    assert response.status_code == 200

    request.node.last_response = data  # register for JSON dump

    expected_result = [
        {"className": "ExternalBase", "inherency": []},
        {"className": "Derived", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "ExternalBase", "type": "IDENTIFIER"}}]}
    ]

    for expected in expected_result:
        assert expected in data, f"Expected {expected} in response"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200

def test_v1_processSourceCode_ClassWithmultiple_inheritance(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/multiple_inheritance"
    }

    logger.info("test_v1_processSourceCode_ClassWithmultiple_inheritance")
    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    data = response.json()
    assert response.status_code == 200

    request.node.last_response = data  # register for JSON dump

    expected_result = [
        {"className": "A", "inherency": []},
        {"className": "B", "inherency": []},
        {"className": "C", "inherency": [
            {"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "A", "type": "IDENTIFIER"}},
            {"first": {"lexeme": "private", "type": "PRIVATE"}, "second": {"lexeme": "B", "type": "IDENTIFIER"}},
        ]},
    ]

    for expected in expected_result:
        assert expected in data, f"Expected {expected} in response"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200

# TODO: Not supported yet - need to handle nested classes in the parser - Process the statement to query classes
# def test_v1_processSourceCode_ClassWithNested(request):
#     input_json = {
#         "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/nested"
#     }

#     logger.info("test_v1_processSourceCode_ClassWithNested")
#     response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
#     data = response.json()
#     assert response.status_code == 200

#     request.node.last_response = data  # register for JSON dump

#     expected_result = [
#         {"className": "Outer", "inherency": []},
#         {"className": "Inner", "inherency": []},
#         {"className": "DerivedNested", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "Outer::Inner", "type": "IDENTIFIER"}}]}
#     ]

#     for expected in expected_result:
#         assert expected in data, f"Expected {expected} in response"

#     logger.info(f"RemoveTempFolder")
#     response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

#     assert response.status_code == 200

# TODO: Not supported yet - need to handle structs in the parser - Process the statement to query classes
# TODO: Not supported yet - need to handle default visibility in the parser - Process the statement to query classes
# def test_v1_processSourceCode_ClassWithStruct_default(request):
#     input_json = {
#         "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/struct_default"
#     }

#     logger.info("test_v1_processSourceCode_ClassWithStruct_default")
#     response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
#     data = response.json()
#     assert response.status_code == 200

#     request.node.last_response = data  # register for JSON dump

#     expected_result = [
#         {"className": "Base", "inherency": []},
#         {"className": "S", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "Base", "type": "IDENTIFIER"}}]},
#         {"className": "Cx", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "Base", "type": "IDENTIFIER"}}]}
#     ]

#     for expected in expected_result:
#         assert expected in data, f"Expected {expected} in response"

#     logger.info(f"RemoveTempFolder")
#     response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

#     assert response.status_code == 200

def test_v1_processSourceCode_ClassWithTemplate_base(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/template_base"
    }

    logger.info("test_v1_processSourceCode_ClassWithTemplate_base")
    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    data = response.json()
    assert response.status_code == 200

    request.node.last_response = data  # register for JSON dump

    # TODO: Is it suppose to be BaseT or BaseT<T> or BaseT<int> ?
    expected_result = [
        {"className": "BaseT", "inherency": []},
        {"className": "Derived", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "BaseT", "type": "IDENTIFIER"}}]}
    ]

    for expected in expected_result:
        assert expected in data, f"Expected {expected} in response"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200

# # TODO: Add virtual token into the lexeme... but how? "virtual public" new token or a "virtual" new token......
# def test_v1_processSourceCode_ClassWithVirtual_diamond(request):
#     input_json = {
#         "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/virtual_diamond"
#     }

#     logger.info("test_v1_processSourceCode_ClassWithVirtual_diamond")
#     response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
#     data = response.json()
#     assert response.status_code == 200

#     request.node.last_response = data  # register for JSON dump

    
#     expected_result = [
#         {"className": "A", "inherency": []},
#         # {"className": "B", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "virtual A", "type": "IDENTIFIER"}}]},
#         # {"className": "C", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "virtual A", "type": "IDENTIFIER"}}]},
#         {"className": "D", "inherency": [
#             {"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "B", "type": "IDENTIFIER"}},
#             {"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "C", "type": "IDENTIFIER"}}
#         ]}
#     ]

#     for expected in expected_result:
#         assert expected in data, f"Expected {expected} in response"

#     logger.info(f"RemoveTempFolder")
#     response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

#     assert response.status_code == 200

def test_v1_processSourceCode_ClassWithSingle_inheritance(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/single_inheritance"
    }

    logger.info("test_v1_processSourceCode_ClassWithSingle_inheritance")
    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    data = response.json()
    assert response.status_code == 200

    request.node.last_response = data  # register for JSON dump

    # TODO: Add virtual token into the lexeme... but how? "virtual public" new token or a "virtual" new token......
    expected_result = [
        {"className": "B", "inherency": []},
        {"className": "A", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "B", "type": "IDENTIFIER"}}]}
    ]

    for expected in expected_result:
        assert expected in data, f"Expected {expected} in response"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200


def test_v1_processSourceCode_ExampleForResults(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/Example"
    }

    logger.info("test_v1_processSourceCode_ExampleForResults")
    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    data = response.json()
    assert response.status_code == 200

    request.node.last_response = data  # register for JSON dump

    # TODO: Add virtual token into the lexeme... but how? "virtual public" new token or a "virtual" new token......
    expected_result = [
        {"className": "Animal", "inherency": []},
        {"className": "Cachorro", "inherency": [{"first": {"lexeme": "private", "type": "PRIVATE"}, "second": {"lexeme": "Animal", "type": "IDENTIFIER"}}]},
        {"className": "Gato", "inherency": [{"first": {"lexeme": "public", "type": "PUBLIC"}, "second": {"lexeme": "Animal", "type": "IDENTIFIER"}}]},
        {"className": "Rato", "inherency": [{"first": {"lexeme": "protected", "type": "PROTECTED"}, "second": {"lexeme": "Animal", "type": "IDENTIFIER"}}]}
    ]

    for expected in expected_result:
        assert expected in data, f"Expected {expected} in response"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200


def test_v1_processSourceCode_ZooExample(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation/observability/source_code_for_testing/ProcessSourceFiles/Zoo"
    }

    logger.info("test_v1_processSourceCode_ZooExample")
    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    data = response.json()
    assert response.status_code == 200

    request.node.last_response = data  # register for JSON dump
    def inh(base: str, access: str = "public"):
        return [{
            "first": {"lexeme": access, "type": access.upper()},
            "second": {"lexeme": base, "type": "IDENTIFIER"}
        }]

    # TODO: Add virtual token into the lexeme... but how? "virtual public" new token or a "virtual" new token......
    expected_result = [
        # ----------------- Bases -----------------
        {"className": "Animal", "inherency": []},
        {"className": "Mamifero", "inherency": inh("Animal")},
        {"className": "Ave", "inherency": inh("Animal", "protected")},
        {"className": "Reptil", "inherency": inh("Animal", "private")},
        {"className": "Peixe", "inherency": inh("Animal")},
        {"className": "Anfibio", "inherency": inh("Animal", "protected")},

        # ----------------- Cadeia de Mamíferos -----------------
        {"className": "Felino", "inherency": inh("Mamifero")},
        {"className": "GrandeFelino", "inherency": inh("Felino", "protected")},
        {"className": "Leao", "inherency": inh("GrandeFelino")},
        {"className": "LeaoAfricano", "inherency": inh("Leao")},
        {"className": "LeaoDoSerengeti", "inherency": inh("LeaoAfricano", "private")},

        # ----------------- Cadeia de Aves -----------------
        {"className": "Passaro", "inherency": inh("Ave", "protected")},
        {"className": "Rapina", "inherency": inh("Passaro")},
        {"className": "Aguia", "inherency": inh("Rapina", "protected")},
        {"className": "AguiaReal", "inherency": inh("Aguia")},
        {"className": "AguiaImperial", "inherency": inh("AguiaReal", "private")},

        # ----------------- Cadeia de Répteis -----------------
        {"className": "Lacertilio", "inherency": inh("Reptil", "private")},
        {"className": "Lagarto", "inherency": inh("Lacertilio")},
        {"className": "Iguana", "inherency": inh("Lagarto", "protected")},
        {"className": "IguanaVerde", "inherency": inh("Iguana")},
        {"className": "IguanaGigante", "inherency": inh("IguanaVerde", "protected")},

        # ----------------- Cadeia de Peixes -----------------
        {"className": "PeixeOssudo", "inherency": inh("Peixe")},
        {"className": "Salmao", "inherency": inh("PeixeOssudo", "protected")},
        {"className": "SalmaoAtlantico", "inherency": inh("Salmao")},
        {"className": "SalmaoDoPacifico", "inherency": inh("SalmaoAtlantico", "private")},
        {"className": "SalmaoGigante", "inherency": inh("SalmaoDoPacifico")},

        # ----------------- Cadeia de Anfíbios -----------------
        {"className": "Anuro", "inherency": inh("Anfibio", "protected")},
        {"className": "Sapo", "inherency": inh("Anuro")},
        {"className": "SapoCururu", "inherency": inh("Sapo", "protected")},
        {"className": "SapoGigante", "inherency": inh("SapoCururu")},
        {"className": "SapoMitologico", "inherency": inh("SapoGigante", "private")},

        # ----------------- Múltipla herança -----------------
        {"className": "PatoAquatico", "inherency": inh("Sapo") + inh("AnimalAquatico")},
        {"className": "Dragao", "inherency": inh("Reptil") + inh("AnimalVoador", "protected") + inh("AnimalAquatico", "private")},

        # ----------------- Recursos -----------------
        {"className": "Recurso", "inherency": []},
        {"className": "Jaula", "inherency": inh("Recurso")},
        {"className": "Viveiro", "inherency": inh("Recurso", "protected")},
        {"className": "Aquario", "inherency": inh("Recurso", "private")},

        # ----------------- Sistemas -----------------
        {"className": "SistemaGerenciamento", "inherency": []},
        {"className": "SistemaFinanceiro", "inherency": inh("SistemaGerenciamento")},
        {"className": "SistemaVisitantes", "inherency": inh("SistemaGerenciamento", "private")},

        # ----------------- Zoológicos -----------------
        {"className": "Zoologico", "inherency": []},
        {"className": "ZoologicoUrbano", "inherency": inh("Zoologico") + inh("SistemaGerenciamento")},
        {"className": "ZoologicoRural", "inherency": inh("Zoologico", "protected") + inh("SistemaFinanceiro", "private")},
        {"className": "ZoologicoDigital", "inherency": inh("Zoologico") + inh("SistemaVisitantes", "protected")},
        {"className": "ZoologicoAquatico", "inherency": inh("Zoologico") + inh("AnimalAquatico", "protected")},
    ]



    for expected in expected_result:
        assert expected in data, f"Expected {expected} in response"

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")

    assert response.status_code == 200


def test_v1_processSourceCode_LargerProject(request):
    input_json = {
        "url": "https://github.com/HugorTorquato/MBA-TCC/tree/Parser/Implementation"
    }
    logger.info(f"test_v1_processSourceCode_LargerProject")
    logger.info(f"Input JSON: {input_json}")

    response = requests.post(f"{BASE_URL}/api/v1/processSourceCode", json=input_json)
    logger.info(f"Response: {response.status_code} - {response.text}")
    data = response.json()
    assert response.status_code == 200  

    request.node.last_response = data  # register for JSON dump

    logger.info(f"RemoveTempFolder")
    response = requests.get(f"{BASE_URL}/api/v1/RemoveTempFolder")
    assert response.status_code == 200
