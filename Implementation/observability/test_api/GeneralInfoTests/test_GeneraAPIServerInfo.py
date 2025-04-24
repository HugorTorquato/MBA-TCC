import requests

from configs.variables import *

def test_health_check():
    response = requests.get(f"{BASE_URL}/api/v1/status")
    assert response.status_code == 200