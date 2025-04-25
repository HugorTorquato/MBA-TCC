import requests
import pytest

from configs.variables import *

response = requests.get(f"{BASE_URL}/api/v1/status")
print(f"Status Code: {response.status_code}")


    #TODO: 
    #   -> Test are suppose to save result metrics in a database
    #       - Maybe a local cach to store data wile tests are running 
    #         ( to voida R/W to database, which can be constly )

if __name__ == "__main__":
    print("Running tests...")
    exit_code = pytest.main(["-vv", "test_api/"])