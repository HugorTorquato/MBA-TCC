import requests

from configs.variables import *

response = requests.get(f"{BASE_URL}/api/v1/status")
print(f"Status Code: {response.status_code}")