#!/bin/bash

if [ "$#" -ne 8 ]; then
    echo "Please enter details in the Following format: $0 <Name> <Address> <Phone> <Email> <Degree> <Major> <University> <GraduationYear>"
    exit 1
fi

NAME=$1
ADDRESS=$2
PHONE=$3
EMAIL=$4
DEGREE=$5
MAJOR=$6
UNIVERSITY=$7
GRADUATION_YEAR=$8

echo "---------------- My Resume ----------------" > resume.txt
echo "" >> resume.txt

echo "===== Personal Details =====" >> resume.txt

echo "Name: $NAME" >> resume.txt
echo "Address: $ADDRESS" >> resume.txt
echo "Phone: $PHONE" >> resume.txt
echo "Email: $EMAIL" >> resume.txt
echo "" >> resume.txt

echo "===== Academic Details =====" >> resume.txt
echo "" >> resume.txt

echo "Education:" >> resume.txt
echo "  Degree: $DEGREE" >> resume.txt
echo "  Major: $MAJOR" >> resume.txt
echo "  University: $UNIVERSITY" >> resume.txt
echo "  Graduation Year: $GRADUATION_YEAR" >> resume.txt
echo "" >> resume.txt

echo "" >> resume.txt

echo "--------------- End of Resume ----------------" >> resume.txt

echo "Open resume.txt for your details"
