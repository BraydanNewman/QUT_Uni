/*
This sql script assumes you have auto commit enabled
*/

DROP DATABASE IF EXISTS BraydanUniversity;
CREATE DATABASE BraydanUniversity;
USE BraydanUniversity;

# Create Unit Table
create table Unit
(
    `Unit.code` VARCHAR(6)   not null,
    `Unit.name` VARCHAR(255) not null,
    description VARCHAR(255) null,
    constraint Unit_pk
        primary key (`Unit.code`)
);
create unique index Unit_code_uindex
    on Unit (`Unit.code`);
create unique index Unit_name_uindex
    on Unit (`Unit.name`);


# Create Tutor Table
create table Tutor
(
    `Tutor.staffID`   int(7) auto_increment,
    `Tutor.staffName` VARCHAR(255) not null,
    constraint Tutor_pk
        primary key (`Tutor.staffID`)
);
create unique index Tutor_staffID_uindex
    on Tutor (`Tutor.staffID`);

# Create Student Table
create table Student
(
    `Student.ID`      int(7) auto_increment,
    `Student.Name`    VARCHAR(255)                     not null,
    `Student.phoneNr` int(10)                          null,
    `Student.gender`  ENUM ('male', 'female', 'other') null,
    constraint Student_pk
        primary key (`Student.ID`)
);
create unique index Student_ID_uindex
    on Student (`Student.ID`);

# Create Table TaughtBy
create table TaughtBy
(
    `Tutor.staffID` int(7)                    not null,
    `Unit.Code`     VARCHAR(6)                not null,
    semestr         ENUM ('1', '2', 'summer') not null,
    constraint TaughtBy_pk
        primary key (`Tutor.staffID`, `Unit.Code`, semestr),
    constraint TaughtBy_Tutor_staffID_fk
        foreign key (`Tutor.staffID`) references Tutor (`Tutor.staffID`),
    constraint TaughtBy_Unit_code_fk
        foreign key (`Unit.Code`) references Unit (`Unit.Code`)
);
create unique index TaughtBy_staffID_Code_semester_uindex
    on TaughtBy (`Tutor.staffID`, `Unit.Code`, semestr);

# Create TuteGroup table
create table TuteGroup
(
    `TuteGroup.Code` VARCHAR(32)      not null,
    `Tutor.staffID`  int(7)           not null,
    date             DATE             not null,
    room             int(8) default 1 null,
    constraint TuteGroup_pk
        primary key (`TuteGroup.Code`),
    constraint TuteGroup_Tutor_staffID_fk
        foreign key (`Tutor.staffID`) references Tutor (`Tutor.staffID`)
);
create unique index TuteGroup_Code_uindex
    on TuteGroup (`TuteGroup.Code`);

# Create TuteEnrollment Table
create table TuteEnrollment
(
    `Student.ID`     int(7)      not null,
    `Unit.code`      VARCHAR(6)  not null,
    `TuteGroup.code` VARCHAR(32) not null,
    constraint TuteEnrollment_pk
        primary key (`Student.ID`, `Unit.code`),
    constraint `TuteEnrollment_Student_Student.ID_fk`
        foreign key (`Student.ID`) references Student (`Student.ID`),
    constraint `TuteEnrollment_TuteGroup_TuteGroup.Code_fk`
        foreign key (`TuteGroup.code`) references TuteGroup (`TuteGroup.Code`),
    constraint `TuteEnrollment_Unit_Unit.code_fk`
        foreign key (`Unit.code`) references Unit (`Unit.code`)
);
create unique index `TuteEnrollment_Student.ID_Unit.code_uindex`
    on TuteEnrollment (`Student.ID`, `Unit.code`);
