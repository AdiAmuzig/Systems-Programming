#### IMPORTS ####
import event_manager as EM


#### PART 1 ####
def fileCorrect(orig_file_path: str, filtered_file_path: str):
    all_lines = createAllCorrectLines(orig_file_path)
    all_lines.sort(key=getId)
    output_file = open(filtered_file_path, 'w')
    for line in all_lines:
        output_file.write(line)
    output_file.close()


def checkLineCorrect(line: str):
    devised_line = line.split(',')
    if len(devised_line) != 5:
        return False

    id_num = (devised_line[0]).replace(' ', '')
    name = ''.join((devised_line[1]).split())
    age = int(devised_line[2].replace(' ', ''))
    birth_year = int(devised_line[3].replace(' ', ''))
    semester = int(devised_line[4].replace(' ', ''))

    id_correct = (len(id_num) == 8 and id_num[0] != '0')
    name_correct = (name.isalpha())
    age_correct = (120 >= age >= 16)
    birth_year_correct = (age + birth_year == 2020)
    semester_correct = (semester >= 1)

    return id_correct and name_correct and age_correct and \
           birth_year_correct and semester_correct


def createAllCorrectLines(orig_file_path: str):
    input_file = open(orig_file_path, 'r')
    all_lines = []

    for new_line in input_file:
        if checkLineCorrect(new_line):
            new_line = correctLine(new_line)
            for i, existing_line in enumerate(all_lines):
                if existing_line[0:8] == new_line[0:8]:
                    del all_lines[i]
            all_lines.append(new_line)

    return all_lines


def correctLine(line: str):
    devised_line = line.split(',')

    id_num = (devised_line[0]).replace(' ', '')
    name = ' '.join((devised_line[1]).split())
    age = devised_line[2].replace(' ', '')
    birth_year = devised_line[3].replace(' ', '')
    semester = devised_line[4].replace(' ', '')
    if semester[-1] != '\n':
        semester = semester + '\n'

    new_line = [id_num, name, age, birth_year, semester]
    new_line = ', '.join(new_line)
    return new_line


def printYoungestStudents(in_file_path: str, out_file_path: str, k: int) -> int:
    if k < 1:
        return -1

    all_lines = createAllCorrectLines(in_file_path)
    if len(all_lines) < k:
        k = len(all_lines)

    all_lines.sort(key=getId)
    all_lines.sort(key=getAge)

    output_file = open(out_file_path, 'w')
    for i, line in enumerate(all_lines):
        if i < k:
            split_line = line.split(', ')
            name = split_line[1] + '\n'
            output_file.write(name)
    output_file.close()

    return k


def getId(line: str):
    split_line = line.split(', ')
    line_id = int(split_line[0])
    return line_id


def getAge(line: str):
    split_line = line.split(', ')
    line_age = int(split_line[2])
    return line_age


def correctAgeAvg(in_file_path: str, semester: int) -> float:
    if semester < 1:
        return -1

    age_sum = 0
    amount_of_students = 0
    all_lines = createAllCorrectLines(in_file_path)

    for line in all_lines:
        split_line = line.split(', ')
        student_semester = int(split_line[-1][0:-1])
        if student_semester == semester:
            amount_of_students = amount_of_students + 1
            age_sum = age_sum + int(split_line[2])

    if amount_of_students == 0:
        average = 0
    else:
        average = age_sum / amount_of_students

    return average


#### PART 2 ####
def printEventsList(events: list, file_path: str):
    em_date = EM.dateCopy(events[1]["date"])
    for event in events:
        if EM.dateCompare(event["date"], em_date) < 0:
            EM.dateDestroy(em_date)
            em_date = EM.dateCopy(event["date"])

    em = EM.createEventManager(em_date)
    EM.dateDestroy(em_date)
    for event in events:
        EM.emAddEventByDate(em, event["name"], event["date"], event["id"])
    EM.emPrintAllEvents(em, file_path)
    return em


def testPrintEventsList(file_path :str):
    events_lists=[{"name":"New Year's Eve","id":1,"date": EM.dateCreate(30, 12, 2020)},\
                    {"name" : "annual Rock & Metal party","id":2,"date":  EM.dateCreate(21, 4, 2021)}, \
                                 {"name" : "Improv","id":3,"date": EM.dateCreate(13, 3, 2021)}, \
                                     {"name" : "Student Festival","id":4,"date": EM.dateCreate(13, 5, 2021)},    ]
    em = printEventsList(events_lists,file_path)
    for event in events_lists:
        EM.dateDestroy(event["date"])
    EM.destroyEventManager(em)

#### Main ####
# feel free to add more tests and change that section.
# # # sys.argv - list of the arguments passed to the python script
if __name__ == "__main__":
    import sys
    fileCorrect('input_test.txt', 'my_out1.txt')
    avg1 = correctAgeAvg('web_input.txt', 3)
    printYoungestStudents('web_input.txt', 'my_out2.txt', 90)
    fileCorrect('input', 'my_out4.txt')
    avg2 = correctAgeAvg('input', 3)
    printYoungestStudents('input', 'my_out5.txt', 9)
    testPrintEventsList('my_out6.txt')
    if len(sys.argv) > 1:
        testPrintEventsList(sys.argv[1])
