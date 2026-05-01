# Laboration 2

1. **How many courses does each department give? Include departments (if any) that do not give any courses.**
```sql
SELECT department.name, COUNT(course.ccode) AS Quantity
FROM department
LEFT JOIN teacher ON department.dcode = teacher.dept
LEFT JOIN course ON teacher.tpid = course.does_teach
GROUP BY department.dcode;
```

2. **List the teachers that do not teach this semester**
```sql
SELECT teacher.forename
FROM teacher
WHERE NOT EXISTS
(
    SELECT *
    FROM course
    WHERE teacher.tpid = course.does_teach
);
```

3. **List the members in the "Course Planning" committee (name, department)**
```sql
SELECT teacher.forename, teacher.dept
FROM teacher
JOIN department ON teacher.dept = department.dcode
JOIN teach_comm ON teacher.tpid = teach_comm.tpid
JOIN committee ON teach_comm.xcode = committee.xcode
WHERE committee.name = "Course Planning";
```

4. **List the teachers that are responsible for more than two courses**
```sql
SELECT teacher.forename, COUNT(teacher.forename) AS QTY
FROM teacher
JOIN course ON teacher.tpid = course.responsible
GROUP BY teacher.forename
HAVING COUNT(teacher.forename) > 2;
```

5. **List the teachers that can teach the course "Linear Algebra"**
```sql
SELECT teacher.forename
FROM teacher
JOIN can_teach ON teacher.tpid = can_teach.tpid
JOIN course ON can_teach.ccode = course.ccode
WHERE course.name = UPPER("Linear Algebra");
```

6. **List, for each student, the number of courses the student takes**
```sql
SELECT students.sname, COUNT(stud_course.SPID) AS "Courses taken"
FROM students
JOIN stud_course ON students.spid = stud_course.SPID
GROUP BY students.sname;
```

7. **List, for each course in Computer Science that has more than four students: the name of the course, the highest grade, the lowest grade, and the average grade on the course**
```sql
SELECT course.name, MIN(stud_course.grade) AS Lowest, MAX(stud_course.grade) AS Highest, AVG(stud_course.grade) AS Average
FROM course
JOIN stud_course ON course.ccode = stud_course.CCODE
JOIN department ON SUBSTRING(course.ccode, 1, 2) = department.dcode
WHERE department.name = "Computer Science"
GROUP BY course.name
HAVING COUNT(stud_course.SPID) > 4;
```

8. **List name and (numeric) grade for the students on the course "CS Introduction" that have received the grade 'C'**
```sql
SELECT DISTINCT students.sname, stud_course.grade
FROM students
JOIN stud_course ON students.spid = stud_course.SPID
JOIN course ON stud_course.CCODE = course.ccode
JOIN grade ON stud_course.grade BETWEEN (SELECT min from grade WHERE letter = "C") AND (SELECT max from grade WHERE letter = "C")
WHERE course.name = UPPER("CS Introduction");
```

9. **List for each course in Mathematics: the name of the course, the number of students and the teacher that does teach the course**
```sql
SELECT course.name AS Course, COUNT(students.spid) AS "Student count", teacher.forename AS Teacher
FROM course
JOIN teacher ON course.does_teach = teacher.tpid
LEFT JOIN stud_course ON course.ccode = stud_course.CCODE
LEFT JOIN students ON stud_course.SPID = students.spid
JOIN department ON SUBSTRING(course.ccode, 1, 2) = department.dcode
WHERE department.name = UPPER("Mathematics")
GROUP BY course.name;
```

10. **List for each student that has failed a course: the student’s name, the name of the course and the grade**
```sql
SELECT DISTINCT students.sname AS "Student name", course.name AS Course, stud_course.grade
FROM students
JOIN stud_course ON students.spid = stud_course.SPID
JOIN course ON stud_course.CCODE = course.ccode
JOIN grade ON stud_course.grade BETWEEN (SELECT min from grade WHERE letter = "F") AND (SELECT max from grade WHERE letter = "F");
```
