#pragma once
#include<iostream>

using namespace std;

const char Path[] = "../testBase4.dat";
const int Size = 4000;

// bd - nas punkt
struct record
{
	char fullName[32]; // <Surname>_<Name>_<Ot4estvo> // Primer - Ïåòpîâ_Èâàí_Ôåäîpîâè÷___________ 
	char streetAdress[18]; // Primer - Ëåíèíà______________
	short int numOfHouse; // nomer doma
	short int numOfFloor; // nomer kvartiri
	char dateOfSettling[10]; // data zaseleniya // Primer - 29-02-65 // Format: dd-mm-yy
};


void printRecord(record* Array, int size);
