#  ____ ____ ____ ____ ____ ____ _________ ____ ____ ____ ____ _________ ____ ____ ____ ____
# ||I |||n |||s |||e |||r |||t |||       |||C |||o |||d |||e |||       |||H |||e |||r |||e ||
# ||__|||__|||__|||__|||__|||__|||_______|||__|||__|||__|||__|||_______|||__|||__|||__|||__||
# |/__\|/__\|/__\|/__\|/__\|/__\|/_______\|/__\|/__\|/__\|/__\|/_______\|/__\|/__\|/__\|/__\|

# DON'T FORGET TO CHANGE the3.place_words TO place_words IF YOU DONT USE IMPORT !!!

# def place_words(Corpus):
#     return False


# Or import the3.py
import the3


#   *   )             )
# ` )  /(   (      ( /( (          (  (
#  ( )(_)) ))\ (   )\()))\   (     )\))(
# (_(_()) /((_))\ (_))/((_)  )\ ) ((_))\
# |_   _|(_)) ((_)| |_  (_) _(_/(  (()(_)
#   | |  / -_)(_-<|  _| | || ' \))/ _` |
#   |_|  \___|/__/ \__| |_||_||_| \__, |
#                                 |___/

# Create Empty Test List
tests = []

# Import sys to read CLI Arguments
import sys

### Options ###

# This means run all tests. You can specify which tests to run by setting this to ["X", "Uber Basic"] etc.
wanted_tests = []

# This means run all tests. You can specify which tests to not run by setting this to ["X", "Uber Basic"] etc.
# Eg. If "X" is specified, every test other than X will run
# !!! This is overwirtes wanted_tests and has more POWER !!!
unwanted_tests = []

# Whether to show calculated solution or not
show_calculated_solution = True

# Whether to show corpus used in the test or not
show_corpus = True

# Whether to show only fails or whole test result
show_only_fails = False

### Options ###

### Check CLI arguments to change options ###

if "-fo" in sys.argv or "--fails-only" in sys.argv:
    show_only_fails = True

if "-nc" in sys.argv or "--no-corpus" in sys.argv:
    show_corpus = False

if "-ncs" in sys.argv or "--no-calculated-solution" in sys.argv:
    show_calculated_solution = False

if "-wt" in sys.argv:

    index = sys.argv.index("-wt")
    if not index == len(sys.argv) - 1:
        wanted_tests = sys.argv[index + 1].split(",")
    for i in xrange(len(wanted_tests)):
        wanted_tests[i] = str.strip(wanted_tests[i])

elif "--wanted-tests" in sys.argv:

    index = sys.argv.index("--wanted-tests")
    if not index == len(sys.argv) - 1:
        wanted_tests = sys.argv[index + 1].split(",")
    for i in xrange(len(wanted_tests)):
        wanted_tests[i] = str.strip(wanted_tests[i])

if "-uwt" in sys.argv:

    index = sys.argv.index("-uwt")
    if not index == len(sys.argv) - 1:
        unwanted_tests = sys.argv[index + 1].split(",")
    for i in xrange(len(unwanted_tests)):
        unwanted_tests[i] = str.strip(unwanted_tests[i])

elif "--unwanted-tests" in sys.argv:

    index = sys.argv.index("--unwanted-tests")
    if not index == len(sys.argv) - 1:
        unwanted_tests = sys.argv[index + 1].split(",")
    for i in xrange(len(unwanted_tests)):
        unwanted_tests[i] = str.strip(unwanted_tests[i])


### Check CLI arguments to change options ###

wanted_tests_length = len(wanted_tests)
unwanted_tests_length = len(unwanted_tests)


### Example Tests ###

# Test X (On the instruction PDF)
if ((wanted_tests_length == 0 or "X" in wanted_tests) and ("X" not in unwanted_tests)):

    test_x_corpus = ["ALI", "SIN", "ASI", "LIR", "IRI", "INI", "KAR"]

    test_x_calculations = the3.place_words(
        test_x_corpus
    )

    test_x_is_false = False

    test_x = (
        "X",
        test_x_calculations,
        test_x_corpus,
        test_x_is_false
    )

    tests.append(test_x)

# Test Uber Basic
if ((wanted_tests_length == 0 or "Uber Basic" in wanted_tests) and ("Uber Basic" not in unwanted_tests)):

    test_uber_basic_corpus = ["ALI", "SIN", "ASI", "LIR", "IRI", "KAR"]

    test_uber_basic_calculations = the3.place_words(
        test_uber_basic_corpus
    )

    test_uber_basic_is_false = True

    test_uber_basic = (
        "Uber Basic",
        test_uber_basic_calculations,
        test_uber_basic_corpus,
        test_uber_basic_is_false
    )

    tests.append(test_uber_basic)

### End Of Example Tests ###


# Insert your own cool named test here

# Right below this comment


# Ok thats enough


import datetime

total_start_time = datetime.datetime.now()

failed_test_count = 0

for test in tests:

    start_time = datetime.datetime.now()

    will_be_printed_result = "\n"

    name, calculations, corpus, is_false = test

    is_failed = False

    will_be_printed_result += " Test " + name + "\n"
    will_be_printed_result += "-" * 30 + "\n"

    if show_corpus:
        will_be_printed_result += "\t(@) Given Corpus: " + str(corpus) + "\n"

    if show_calculated_solution:
        will_be_printed_result += "\t(@) Calculations: " + \
            str(calculations) + "\n\n"

    if is_false is True:
        if calculations == False:
            will_be_printed_result += "\t(~) Passed: Correct result is false and also calculations are false"
        else:
            will_be_printed_result += "\t(!) Failed: Correct result is false but calculations are not"
            is_failed = True
        will_be_printed_result += "\n"

    else:

        upperCorpus = [x.upper() for x in corpus]

        correct_grid_length = len(corpus[0])
        solution_length = len(calculations)

        if solution_length != correct_grid_length:
            will_be_printed_result += "\t(!) Failed: Correct solution must have " + str(
                correct_grid_length) + " items, but calculations has " + str(solution_length)
            is_failed = True
        else:
            will_be_printed_result += "\t(~) Passed: Correct solution has " + str(
                correct_grid_length) + " items, calculations also has " + str(solution_length)

        will_be_printed_result += "\n\n"

        is_upper_correct = True

        for i in xrange(solution_length):
            if calculations[i] != calculations[i].upper():
                is_upper_correct = False

        if is_upper_correct == False:
            will_be_printed_result += "\t(!) Failed: Every item of correct solution must be fully upper case"
            is_failed = True
        else:
            will_be_printed_result += "\t(~) Passed: Every item of correct solution is fully upper case"

        will_be_printed_result += "\n\n"

        for current_word in calculations:

            is_included_in_corpus = False

            current_words_count_in_calculations = 0

            if current_word in upperCorpus:

                is_included_in_corpus = True

            for current_word_test in calculations:
                if current_word_test == current_word:
                    current_words_count_in_calculations += 1

            for i in xrange(solution_length):
                current_word_test = ""
                for j in xrange(solution_length):
                    current_word_test += calculations[j][i]
                if current_word_test == current_word:
                    current_words_count_in_calculations += 1

            if is_included_in_corpus is True and current_words_count_in_calculations == 1:
                will_be_printed_result += "\t(~) Passed: " + str(
                    current_word) + " was in corpus and appears only once in calculations"

            elif is_included_in_corpus is True and current_words_count_in_calculations != 1:
                more_or_less = "more" if current_words_count_in_calculations > 1 else "less"
                will_be_printed_result += "\t(!) Failed: " + str(
                    current_word) + " was in corpus but appears " + more_or_less + " than once in calculations"
                is_failed = True

            elif is_included_in_corpus is False and current_words_count_in_calculations != 1:
                more_or_less = "more" if current_words_count_in_calculations > 1 else "less"
                will_be_printed_result += "\t(!) Failed: " + str(
                    current_word) + " was not in corpus and appears " + more_or_less + " than once in calculations"
                is_failed = True

            else:
                will_be_printed_result += "\t(!) Failed: " + str(
                    current_word) + " was not in corpus but appears only once in calculations"
                is_failed = True

            will_be_printed_result += "\n"

        for i in xrange(solution_length):

            current_word = ""

            for j in xrange(solution_length):
                current_word += calculations[j][i]

            is_included_in_corpus = False

            current_words_count_in_calculations = 0

            if current_word in upperCorpus:

                is_included_in_corpus = True

            for current_word_test in calculations:
                if current_word_test == current_word:
                    current_words_count_in_calculations += 1

            for i in xrange(solution_length):
                current_word_test = ""
                for j in xrange(solution_length):
                    current_word_test += calculations[j][i]
                if current_word_test == current_word:
                    current_words_count_in_calculations += 1

            if is_included_in_corpus is True and current_words_count_in_calculations == 1:
                will_be_printed_result += "\t(~) Passed: " + str(
                    current_word) + " was in corpus and appears only once in calculations"

            elif is_included_in_corpus is True and current_words_count_in_calculations != 1:
                more_or_less = "more" if current_words_count_in_calculations > 1 else "less"
                will_be_printed_result += "\t(!) Failed: " + str(
                    current_word) + " was in corpus but appears " + more_or_less + " than once in calculations"
                is_failed = True

            elif is_included_in_corpus is False and current_words_count_in_calculations != 1:
                more_or_less = "more" if current_words_count_in_calculations > 1 else "less"
                will_be_printed_result += "\t(!) Failed: " + str(
                    current_word) + " was not in corpus and appears " + more_or_less + " than once in calculations"
                is_failed = True

            else:
                will_be_printed_result += "\t(!) Failed: " + str(
                    current_word) + " was not in corpus but appears only once in calculations"
                is_failed = True

            will_be_printed_result += "\n"

    will_be_printed_result += "\n"

    finish_time = datetime.datetime.now()

    if is_failed:
        failed_test_count = failed_test_count + 1
        will_be_printed_result += "\t(!) Test " + name + " failed. (In " + str(
            (finish_time - start_time).total_seconds() * 1000) + " milliseconds)"

    else:
        will_be_printed_result += "\t(~) Test " + name + " passed. (In " + str(
            (finish_time - start_time).total_seconds() * 1000) + " milliseconds)"

    will_be_printed_result += "\n"

    if show_only_fails:
        if is_failed:
            print will_be_printed_result
    else:
        print will_be_printed_result

total_finish_time = datetime.datetime.now()

print "--- Tested", len(tests), "conditions,", failed_test_count, "failed", len(tests) - failed_test_count, "passed. (In " + str((total_finish_time - total_start_time).total_seconds() * 1000) + " milliseconds) ---"