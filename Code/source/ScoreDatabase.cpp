 #include "ScoreDatabase.h"

#include <sstream>
#include <iostream>	


sqlite3 *ScoreDatabase::s_db;
const char *ScoreDatabase::s_dbname = "m.db";


/* Opens a file to be used for the database   If the file does not exist it is created
*/
void ScoreDatabase::open()
{ 

	std::cout << sqlite3_open(s_dbname, &s_db) << std::endl;

	sqlite3_open(s_dbname, &s_db);
	std::cout << sqlite3_exec(s_db, "CREATE TABLE IF NOT EXISTS scores(name TEXT, score INT);", 0, 0, 0) << std::endl;
	
}

// when called adds a new score to teh DB as Name of winner and Difference in score

void ScoreDatabase::addScore(const char *a_name, int a_score)
{
	std::stringstream ss;


	ss << "INSERT INTO scores(name, score) VALUES (" << "'" << a_name << "'," << a_score << ");";
	std::cout << ss.str() << std::endl;
	std::cout << sqlite3_exec(s_db, ss.str().c_str(), 0, 0, 0) << std::endl;	
}

// Buffers threw the Scores to find all the scores and displaces it

static int pscores_cback_internal(void* a_count, int numArgs, char **data, char ** columnName)
{
	int &count = *(int*)a_count;

	DrawString(data[0], 200, 700 - count * 40);
	DrawString(data[1], 400, 700 - count * 40);

	count++;
	return 0;
}


// Draws to the System console and calls the pscore wich draws to the game screen.
void ScoreDatabase::draw()
{
	int count = 0;
	std::cout << sqlite3_exec(s_db, "SELECT * from scores order by score desc;", pscores_cback_internal, &count, 0) << std::endl;

}

// closes data base

void ScoreDatabase::close()
{
	std::cout << sqlite3_close(s_db) << std::endl;
}