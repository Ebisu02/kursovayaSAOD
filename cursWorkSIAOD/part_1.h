#pragma once
#include<iostream>

using namespace std;

const char Path[] = "../testBase4.dat";
const int Size = 4000;

struct record
{
	char fullName[32];
	char streetAdress[18];
	short int numOfHouse; 
	short int numOfFloor;
	char dateOfSettling[10]; 
};


void print_record(record* Array, int size);
