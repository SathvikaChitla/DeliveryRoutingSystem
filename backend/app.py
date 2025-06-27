from flask import Flask, request, jsonify
from flask_cors import CORS
import csv
import subprocess

app = Flask(__name__)
CORS(app)


@app.route("/cities", methods=["GET"])
def get_cities():
    cities = []
    with open("../data/cities.csv", "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            cities.append(row["City"])
    return jsonify(cities)


@app.route("/route", methods=["POST"])
def get_route():
    data = request.json
    source = data["source"]
    destination = data["destination"]
    weight = str(data["weight"])
    mode = data["mode"]

    exe_path = "../build/delivery_routing.exe"
    cpp_input = f"{source}\n{destination}\n{weight}\n{mode}\n"

    print("Calling exe with input:")
    print(cpp_input)

    try:
        result = subprocess.run(
            [exe_path],
            input=cpp_input,
            capture_output=True,
            text=True,
            encoding="utf-8"
        )

        print("STDOUT:", result.stdout)
        print("STDERR:", result.stderr)

        if not result.stdout:
            raise ValueError("C++ EXE gave no output.")

        lines = result.stdout.strip().split("\n")
        path = lines[0].split(":")[-1].strip().split()
        distance = float(lines[1].split(":")[-1].replace("km", "").strip())
        cost = float(lines[2].split("₹")[-1].strip())

        return jsonify({
            "path": path,
            "distance": distance,
            "cost": cost
        })

    except Exception as e:
        return jsonify({"error": str(e)}), 500


if __name__ == "__main__":
    app.run(debug=True)
