/*
 *  ΠΑΝΕΠΙΣΤΗΜΙΟ ΠΑΤΡΩΝ
 *  ΤΜΗΜΑ ΗΛΕΚΤΡΟΛΟΓΩΝ ΜΗΧΑΝΙΚΩΝ
 *  ΜΑΘΗΜΑ: ΑΡΧΕΣ ΠΡΟΓΡΑΜΜΑΤΙΣΜΟΥ
 *
 *  Χειρισμός ASCII αρχείων που περιέχουν εγγραφές καταγραφής
 *  ελάχιστης και μέγιστης θερμοκρασίας σε ένα δίκτυο αισθητήρων
 *
 *  ΠΑΤΡΑ 12-5-2014
 *
 *
 *  Τα δεδομένα κάθε εγγραφής αποθηκεύονται σε δομή τύπου

typedef struct {
	unsigned short int sensID ;		// κωδικός αριθμός αισθητήρα
	short int minTmp ;				// ελάχιστη θερμοκρασία
	short int maxTmp ;				// μέγιστη θερμοκρασία
	unsigned int Time ;				// χρόνος λήψης
} SENSOR ;

Στο αρχείο αποθηκεύονται σαν ASCII αριθμοί χωρισμένοι με ένα κενο, μία εγγραφή ανά γραμμή
 *
 *  Εχουν υλοποιηθεί οι εξής συναρτήσεις
 *
 *  initSensorFile:		Τοποθέτηση τυχαίων εγγραφών σε αρχείο
 *  appendSensorFile:	Προσθήκη νέων εγγραφών στο τέλος του αρχείου
 *  printSensorFile:	Εκτύπωση των μη διαγραφέντων εγγραφών του αρχείου
 *  printSensorMeasures:Εκτύπωση των εγγραφών συγκεκριμένου αισθητήρα
 *  deleteSensorRecords:Διαγραφή εγγραφών συγκεκριμένου αισθητήρα
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Εγγραφή μέτρησης ελάχιστης (minTmp) και μέγιστης (maxTmp) θερμοκρασίας
// για τον αισθητήρα που έχει κωδικό αριθμό (sensID)
typedef struct {
	unsigned short int sensID ;		// κωδικός αριθμός αισθητήρα
	short int minTmp ;				// ελάχιστη θερμοκρασία
	short int maxTmp ;				// μέγιστη θερμοκρασία
	unsigned int Time ;				// χρόνος λήψης
} SENSOR ;


// ***********************************************************************
// Πρωτότυπα συναρτήσεων
// ***********************************************************************
int initSensorFile( char *filename, int num ) ;
int appendSensorFile( char *filename, int num ) ;
int printSensorFile( char *filename ) ;
int printSensorMeasures( char *filename, unsigned short int sID  ) ;
int deleteSensorRecords( char *filename, unsigned short int sID ) ;


/********************************************************************************
Δημιουργία του αρχείου filename το οποίο έχει num εγγραφές τύπου SENSOR
Το περιεχόμενο των εγγραφών είναι τυχαίο
Επιστρέφει 0 σε επιτυχία, αρνητικό νούμερο σε σφάλμα
*******************************************************************************/
int initSensorFile( char *filename, int num )
{
	SENSOR s1 ;
	FILE *fp ;
	int i ;

	// ανοίγω το αρχείο το όνομα του οποίου περιέχεται στην μεταβλητή filename για εγγραφή
	if ( ( fp=fopen( filename, "wt")) == NULL )
		return -1 ;

	for( i = 0 ; i < num ; i++ )
	{
		// τοποθετώ τυχαίο ακέραιο που βρίσκεται στο διάστημα [i,i+2] σαν μέτρηση χρόνου (s1.Time)
		s1.Time = i+rand()%3 ;
		// τοποθετώ τυχαίο ακέραιο που βρίσκεται στο διάστημα [0,1000) σαν κωδικό νούμερο αισθητήρα (s1.sensID)
		s1.sensID = rand()%1000 ;
		// τοποθετώ τυχαίο ακέραιο που βρίσκεται στο διάστημα [-50,50) σαν ελάχιστη θερμοκρασία (s1.minTmp)
		s1. minTmp = (rand()%100) - 50 ;
		// τοποθετώ τυχαίο ακέραιο που βρίσκεται στο διάστημα [-25,75) σαν μέγιστη θερμοκρασία (s1.maxTmp)
		// φροντίζοντας πάντα η θερμοκρασία αυτή να είναι μεγαλύτερη ή ίση της s1.minTmp
		while ( (s1. maxTmp = (rand()%100) - 25) < s1.minTmp ) ;
		// Το περιεχόμενο της μεταβλητής s1 αποθηκεύεται στο αρχείο fp
		if ( fprintf( fp, "%hu %u %hd %hd\n", s1.sensID,s1.Time,s1.minTmp,s1.maxTmp) < 1)
		{
			fclose(fp) ;
			return -2 ;
		}
	}
	// κλείνω το αρχείο fp
	fclose(fp) ;
	return 0 ;
}


/********************************************************************************
Ανοίγει το αρχείο filename στο οποίο προσθέτει στο τέλος του num εγγραφές τύπου SENSOR
Το περιεχόμενο των εγγραφών είναι τυχαίο
Επιστρέφει 0 σε επιτυχία, αρνητικό νούμερο σε σφάλμα
*******************************************************************************/
int appendSensorFile( char *filename, int num )
{
	SENSOR s1 ;
	FILE *fp ;
	int i ;

	// ανοίγω το αρχείο το όνομα του οποίου περιέχεται στην μεταβλητή filename για προσθήκη στο τέλος του αρχείου
	if ( ( fp=fopen( filename, "at")) == NULL )
		return -1 ;

	for( i = 0 ; i < num ; i++ )
	{
		// τοποθετώ τυχαίο ακέραιο που βρίσκεται στο διάστημα [i,i+2] σαν μέτρηση χρόνου (s1.Time)
		s1.Time = i+rand()%3 ;
		// τοποθετώ τυχαίο ακέραιο που βρίσκεται στο διάστημα [0,1000) σαν κωδικό νούμερο αισθητήρα (s1.sensID)
		s1.sensID = rand()%1000 ;
		// τοποθετώ τυχαίο ακέραιο που βρίσκεται στο διάστημα [-50,50) σαν ελάχιστη θερμοκρασία (s1.minTmp)
		s1. minTmp = (rand()%100) - 50 ;
		// τοποθετώ τυχαίο ακέραιο που βρίσκεται στο διάστημα [-25,75) σαν μέγιστη θερμοκρασία (s1.maxTmp)
		// φροντίζοντας πάντα η θερμοκρασία αυτή να είναι μεγαλύτερη ή ίση της s1.minTmp
		while ( (s1. maxTmp = (rand()%100) - 25) < s1.minTmp ) ;
		// Το περιεχόμενο της μεταβλητής s1 αποθηκεύεται στο αρχείο fp
		if ( fprintf( fp, "%hu %u %hd %hd\n", s1.sensID,s1.Time,s1.minTmp,s1.maxTmp) < 1)
		{
			fclose(fp) ;
			return -2 ;
		}
	}
	// κλείνω το αρχείο fp
	fclose(fp) ;
	return 0 ;
}

/********************************************************************************
Ανοιγμα του αρχείου filename το οποίο έχει εγγραφές τύπου SENSOR για διάβασμα
και εκτύπωση του περιεχομένου των εγγραφών.
Επιστρέφει έναν ακέραιο, τον αριθμό των εγγραφών που τυπώθηκαν, αρνητικό νούμερο σε σφάλμα
*******************************************************************************/
int printSensorFile( char *filename )
{
	SENSOR s1 ;
	FILE *fp ;
	unsigned int i ;
	char B[100] ;

	// ανοίγω το αρχείο για διάβασμα το όνομα του οποίου περιέχεται στην μεταβλητή filename
	if ( ( fp=fopen( filename, "rt")) == NULL )
		return -1 ;
	printf( "\n\n\n" ) ;
	i = 0 ;
	// Το περιεχόμενο μιας εγγραφής μεταφέρεται στην μεταβλητή κειμένου B
	while ( fgets( B, 99, fp) == B )
	{
		// Το περιεχόμενο της μεταβλητής B χωρίζεται στις μεταβλητές της δομής SENSOR
		// και τυπώνεται αν δεν έχει διαγραφεί
		if ( 4 == sscanf( B, "%hu %u %hd %hd", &(s1.sensID),&(s1.Time),&(s1.minTmp),&(s1.maxTmp)))
			printf( "%7u %7hu %7u %7hd %7hd\n", ++i, s1.sensID,s1.Time,s1.minTmp,s1.maxTmp) ;
	}
	fclose(fp) ;
	return i ;
}



/********************************************************************************
Ανοιγμα του αρχείου filename το οποίο έχει εγγραφές τύπου SENSOR και εκτύπωση
των μετρήσεων του αισθητήρα με τον κωδικό αριθμό sID.
Επιστρέφει έναν ακέραιο, τον αριθμό των εγγραφών που τυπώθηκαν στην οθόνη, αρνητικό νούμερο σε σφάλμα
*******************************************************************************/
int printSensorMeasures( char *filename, unsigned short int sID  )
{
	SENSOR s1 ;
	FILE *fp ;
	unsigned int i ;
	char B[100] ;

	// ανοίγω το αρχείο για διάβασμα το όνομα του οποίου περιέχεται στην μεταβλητή filename
	if ( ( fp=fopen( filename, "rt")) == NULL )
		return -1 ;
	printf( "\n\n\n" ) ;
	i = 0 ;
	// Το περιεχόμενο μιας εγγραφής μεταφέρεται στην μεταβλητή κειμένου B
	while ( fgets( B, 99, fp) == B )
	{
		// Το περιεχόμενο της μεταβλητής B χωρίζεται στις μεταβλητές της δομής SENSOR
		// και τυπώνεται αν δεν έχει διαγραφεί
		if ( 4 == sscanf( B, "%hu %u %hd %hd", &(s1.sensID),&(s1.Time),&(s1.minTmp),&(s1.maxTmp)))
			if ( s1.sensID == sID )
				printf( "%7u %7hu %7u %7hd %7hd\n", ++i, s1.sensID,s1.Time,s1.minTmp,s1.maxTmp) ;
	}
	fclose(fp) ;
	return i ;
}


/********************************************************************************
Ανοιγμα του αρχείου filename το οποίο έχει εγγραφές τύπου SENSOR για διάβασμα/γράψιμο
Διαγράφει τις εγγραφές του αισθητήρα που έχουν κωδικό αριθμό sID. Η διαγραφή πραγματοποιείται σβήνοντας τα περιεχόμενα της γραμμής
Επιστρέφει έναν ακέραιο, τον αριθμό των εγγραφών που διαγράφηκαν, αρνητικό νούμερο σε σφάλμα
*******************************************************************************/
int deleteSensorRecords( char *filename, unsigned short int sID )
{
	SENSOR s1 ;
	FILE *fp ;
	unsigned int i ;
	char B[100] ;

	// ανοίγω το αρχείο για διάβασμα το όνομα του οποίου περιέχεται στην μεταβλητή filename
	if ( ( fp=fopen( filename, "r+t")) == NULL )
		return -1 ;
	i = 0 ;
	// Το περιεχόμενο μιας εγγραφής μεταφέρεται στην μεταβλητή κειμένου B
	while ( fgets( B, 99, fp) == B )
	{
		// Το περιεχόμενο της μεταβλητής B χωρίζεται στις μεταβλητές της δομής SENSOR
		if ( 4 != sscanf( B, "%hu %u %hd %hd", &(s1.sensID),&(s1.Time),&(s1.minTmp),&(s1.maxTmp)))
			continue ;
		// Αν βρεθεί εγγραφή που πρέπει να διαγραφεί τότε
		if ( s1.sensID == sID)
		{
			// Υπολογίζουμε τον αριθμό των bytes που διαβάστηκαν στην προηγούμενη γραμμή του αρχείου
			int k = strlen(B) ;
			// ξαναγυρνάμε μια εγγραφή/γραμμή πίσω
			fseek( fp, -k, SEEK_CUR ) ;
			// τοποθετούμε στο Β τον κενό χαρακτήρα έτσι ώστε να σβήσουμε τα δεδομένα που είναι γραμμένα
			// αφήνοντας μόνο τον χαρακτήρα \n στο τέλος της γραμμής
			memset( B, ' ', strlen(B)-1) ;
			// τοποθετούμε το περιεχόμενο του Β στο αρχείο για να σβήσουμε το προηγούμενο περιεχόμενο
			if ( fputs( B, fp ) < 0)
			{
				fclose(fp) ;
				return -1 ;
			}
			i++ ;
		}
	}
	fclose(fp) ;
	return i ;
}






// *******************************************************************************
int main(void)
{

	// δημιουργείται το αρχείο sensor.dat το οποίο έχει 100 εγγραφές
	if ( initSensorFile( "sensor.dat", 100 ) == 0 )
	{
		// τυπώνει τις εγγραφές του αρχείου και το πλήθος τους
		printf( "\n\nTotal number of Records: %d\n", printSensorFile( "sensor.dat" ) ) ;

		// τυπώνει τις εγγραφές του αισθητήρα με αριθμό 33
		printf( "\n\nTotal number of Records for sensor %d: %d\n", 33, printSensorMeasures( "sensor.dat", (unsigned short int)33 ) ) ;

		// προσθέτει 10 εγγραφές στο τέλος του αρχείου sensor.dat
		appendSensorFile( "sensor.dat", 10 ) ;

		// τυπώνει τις εγγραφές του αρχείου και το πλήθος τους
		printf( "\n\nTotal number of Records: %d\n", printSensorFile( "sensor.dat" ) ) ;

		// τυπώνει τις εγγραφές του αισθητήρα με αριθμό 33
		printf( "\n\nTotal number of Records for sensor %d: %d\n", 33, printSensorMeasures( "sensor.dat", (unsigned short int)33 ) ) ;

		printf( "Sensor %d records deleted: %d\n", 33, deleteSensorRecords( "sensor.dat", (unsigned short int)33 ) ) ;

		// τυπώνει τις εγγραφές του αρχείου και το πλήθος τους
		printf( "\n\nTotal number of Records: %d\n", printSensorFile( "sensor.dat" ) ) ;

		// τυπώνει τις εγγραφές του αισθητήρα με αριθμό 33
		printf( "\n\nTotal number of Records for sensor %d: %d\n", 33, printSensorMeasures( "sensor.dat", (unsigned short int)33 ) ) ;

	}

	return EXIT_SUCCESS;
}
