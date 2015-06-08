import argparse

import csv

# fill out the following function
def count_n_most_popular_baby_names_by_county(baby_names_csv, n, year):
  #The return value should look like {COUNTY_NAME : [MOST_POPULAR_NAME, 2nd_MOST_POPULAR_NAME, ...]
  #return {'WESTCHESTER' : ['BOB', 'DAVE']}  

    # i am assuming (year, name, county) doesn't have duplicates in the file
    # this assumption is false as there could be male or female
    unsorted = {} # dictionary of dictionary by county then by name
    reader = csv.reader(baby_names_csv, delimiter=',')
    next(reader) # skips header row
    for row in reader:
        if row[0] == year:
            if row[2] in unsorted:
                if row[1] in unsorted[row[2]]:
                    unsorted[row[2]][row[1]] += int(row[4])
                else:
                    unsorted[row[2]][row[1]] = int(row[4])
            else:
                unsorted[row[2]] = {row[1]: int(row[4])}

    # i just read that using compare function is slow, but its the quickest way for me
    # to implement in limited time
    def compare(tup1, tup2):
        if tup1[1] > tup2[1]:
            return -1
        elif tup1[1] < tup2[1]:
            return 1
        elif tup1[0] > tup2[0]:
            return -1
        elif tup1[0] < tup2[0]:
            return 1
        else:
            raise Exception("unexpected")

    sorted_result = {}
    for county, names in unsorted.iteritems():
        sorted_result[county] = [tup[0] for tup in sorted(names.iteritems(), cmp=compare)[0:n]]

    return sorted_result

def main(): 
    parser = argparse.ArgumentParser(description='Generates statistics on baby names.')
    parser.add_argument('baby_names_csv', help='Path to Baby_Names__Beginning_2007.csv', type=file)
    parser.add_argument('n', help='number of names to return per country', type=int)
    parser.add_argument('year', help='the year under consideration')
    args = parser.parse_args()

    print count_n_most_popular_baby_names_by_county(args.baby_names_csv, args.n, args.year)


if __name__ == "__main__":
  main()
