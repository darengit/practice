clean:
	find . -type f -name "*.py[co]" -delete
	find . -type d -name "__pycache__" -delete
test: 
	python3.4 tests/services/add.py
	python3.4 tests/utils/db.py
