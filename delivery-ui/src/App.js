import React, { useState, useEffect } from "react";
import "./index.css"; // Tailwind CSS

function App() {
  const [cities, setCities] = useState([]);
  const [source, setSource] = useState("");
  const [destination, setDestination] = useState("");
  const [weight, setWeight] = useState("");
  const [mode, setMode] = useState("economy");
  const [result, setResult] = useState(null);
  const [error, setError] = useState(null);

  useEffect(() => {
    fetch("http://localhost:5000/cities")
      .then((res) => res.json())
      .then((data) => setCities(data))
      .catch(() => setError("Failed to fetch cities"));
  }, []);

  const handleSubmit = async (e) => {
    e.preventDefault();
    setError(null);
    setResult(null);

    try {
      const response = await fetch("http://localhost:5000/route", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ source, destination, weight, mode }),
      });

      const data = await response.json();
      if (!response.ok) throw new Error(data.error || "Request failed");

      setResult(data);
    } catch (err) {
      setError(err.message);
    }
  };

  return (
    <div className="min-h-screen bg-gradient-to-br from-blue-100 to-purple-100 flex items-center justify-center px-4 py-12">
      <div className="bg-white shadow-2xl rounded-2xl w-full max-w-2xl p-8 space-y-6">



        {/* App Title */}
        <h2 className="text-2xl font-bold text-center text-blue-800 flex items-center justify-center gap-2">
          🚚 Delivery Route Optimizer
        </h2>

        {/* Form */}
        <form className="grid grid-cols-1 sm:grid-cols-2 gap-4" onSubmit={handleSubmit}>

          {/* Source City */}
          <div>
            <label className="block font-medium text-gray-700 mb-1">Source City</label>
            <select
              value={source}
              onChange={(e) => setSource(e.target.value)}
              required
              className="w-full p-2 border border-gray-300 rounded"
            >
              <option value="">Select Source</option>
              {cities.map((city) => (
                <option key={city} value={city}>{city}</option>
              ))}
            </select>
          </div>

          {/* Destination City */}
          <div>
            <label className="block font-medium text-gray-700 mb-1">Destination City</label>
            <select
              value={destination}
              onChange={(e) => setDestination(e.target.value)}
              required
              className="w-full p-2 border border-gray-300 rounded"
            >
              <option value="">Select Destination</option>
              {cities.map((city) => (
                <option key={city} value={city}>{city}</option>
              ))}
            </select>
          </div>

          {/* Package Weight */}
          <div>
            <label className="block font-medium text-gray-700 mb-1">Package Weight (in grams)</label>
            <select
              value={weight}
              onChange={(e) => setWeight(e.target.value)}
              required
              className="w-full p-2 border border-gray-300 rounded"
            >
              <option value="">Select Weight</option>
              <option value={100}>0 – 200g</option>
              <option value={300}>200 – 500g</option>
              <option value={750}>500g – 1kg</option>
              <option value={1500}>1kg – 2kg</option>
              <option value={2500}>2kg – 3kg</option>
              <option value={3500}>3kg – 4kg</option>
              <option value={4500}>4kg – 5kg</option>
              <option value={6000}>5kg – 6kg</option>
              <option value={7000}>6kg – 7kg</option>
              <option value={8000}>7kg – 8kg</option>
              <option value={9000}>8kg – 9kg</option>
              <option value={10000}>9kg – 10kg</option>
            </select>
          </div>

          {/* Delivery Mode */}
          <div>
            <label className="block font-medium text-gray-700 mb-1">Delivery Mode</label>
            <select
              value={mode}
              onChange={(e) => setMode(e.target.value)}
              required
              className="w-full p-2 border border-gray-300 rounded"
            >
              <option value="economy">Economy</option>
              <option value="express">Express</option>
            </select>
          </div>

          {/* Submit Button */}
          <div className="sm:col-span-2">
            <button
              type="submit"
              className="w-full bg-blue-600 text-white py-2 rounded hover:bg-blue-700 transition"
            >
              Calculate
            </button>
          </div>
        </form>

        {/* Error Display */}
        {error && (
          <div className="text-red-600 font-semibold text-center">
            ❌ {error}
          </div>
        )}

        {/* Result Display */}
        {result && (
          <div className="bg-gray-50 border border-gray-300 rounded-lg p-4 text-center space-y-2">
            <h3 className="text-lg font-semibold text-pink-600">📍 Optimal Path:</h3>
            <p>{result.path.join(" → ")}</p>
            <p>🛣️ <span className="font-semibold">Total Distance:</span> {result.distance} km</p>
            <p>💸 <span className="font-semibold">Estimated {mode} cost:</span> ₹{result.cost}</p>
          </div>
        )}
      </div>
    </div>
  );
}

export default App;
