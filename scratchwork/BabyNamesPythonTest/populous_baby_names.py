import argparse
import sqlite3 
import os 

def create_database():
  try:
    os.remove('baby_names.db')
  except OSError:
    pass

  conn = sqlite3.connect('baby_names.db')

  c = conn.cursor()

  c.execute('''CREATE TABLE baby_names(year TEXT, name TEXT, county TEXT, sex TEXT, count INT)''')
  c.execute('''CREATE TABLE population(county TEXT, Population12 INT, Population10 INT, Area INT, Density INT)''')
  conn.commit()

  return conn

def populate_baby_name_table(conn, baby_names_csv): 
  #read first line 
  data= [line.split(',') for line in baby_names_csv]
  c = conn.cursor()
  c.executemany('INSERT INTO baby_names VALUES(?, ?, ?, ?, ?)', data[1::])
  conn.commit();

def populate_population_table(conn, population_ny_csv): 
  #read first line 
  data= [line.split(',') for line in population_ny_csv]
  c = conn.cursor()
  c.executemany('INSERT INTO population VALUES(?, ?, ?, ?, ?)', data[1::])
  conn.commit()

def populous_baby_names_query(conn, starting_letter):
  c = conn.cursor()

  # Complete the included Python script, populous_baby_names.py by modifying the SQL statement (the variable sql_statement) to be executed within c.execute(...) 
  # The SQl statement should return all unique male baby names in 2012 in the most populous county as determined by the 2012 population estimate. In addition, all names must start with the chosen starting_letter.

  # there could be a tie with county population for top, in that case this query would return all results from counties tied for the top spot
  sql_statement = """SELECT DISTINCT n.name FROM baby_names n
                       INNER JOIN population p ON n.county = p.county
                     WHERE sex="M"
                       AND n.year=2012
                       AND name LIKE "{}%"
                       AND p.Population12=(SELECT MAX(Population12) FROM population)""".format(starting_letter) # CHANGE ME
  answer = []
  for row in c.execute(sql_statement):
    answer.append(str(row[0]))
  return answer

def main(): 
    parser = argparse.ArgumentParser(description='Generates statistics on baby names.')
    parser.add_argument('baby_names_csv', help='Path to Baby_Names__Beginning_2007.csv', type=file)
    parser.add_argument('population_csv', help='Path to population_ny.csv', type=file)
    parser.add_argument('starting_letter', help='Starting letter')
    args = parser.parse_args()

    conn= create_database()
    populate_population_table(conn, args.population_csv)
    populate_baby_name_table(conn, args.baby_names_csv)

    print populous_baby_names_query(conn, args.starting_letter)

if __name__ == "__main__":
  main()
