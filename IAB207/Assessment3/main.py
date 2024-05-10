from website import create_app

# keep it simple
app = create_app()

if __name__ == "__main__":
    app.run(debug=True)
# app.run(host='0.0.0.0', port=5000, debug=True, threaded=True)
