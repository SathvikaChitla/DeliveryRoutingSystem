import requests

payload = {
    "source": "Kolkata",
    "destination": "Kharagpur",
    "weight": 2500,
    "mode": "economy"
}

response = requests.post("http://127.0.0.1:5000/route", json=payload)

print("Status Code:", response.status_code)
print("Response JSON:", response.json())
