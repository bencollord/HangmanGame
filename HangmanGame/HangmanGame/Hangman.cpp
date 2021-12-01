#include <string>
#include <sstream>
#include "Utilities.h"
#include "Hangman.h"

using namespace std;
using namespace Utilities;

namespace HangmanGame
{
	Miss::Miss(string bPart)
	{
		this->bPart = bPart;
		this->val = NULL;
		this->empty = string(bPart.length(), ' ');
	}

	char Miss::value()
	{
		return this->val;
	}

	void Miss::value(char value)
	{
		this->val = value;
	}

	bool Miss::isActive()
	{
		return this->val != NULL;
	}

	string Miss::print()
	{
		if (this->isActive())
		{
			return this->bPart;
		}

		return this->empty;
	}

	Hangman::Hangman(string word)
	{
		this->word = word;
		this->result.resize(this->word.size());
		this->guesses = 0;

		for (int i = 0; i < this->word.size(); ++i)
		{
			this->result[i] = isblank(this->word[i]) ? this->word[i] : UNKNOWN_CHAR;
		}

		this->loadMisses();
	}

	void Hangman::guess(char c)
	{
		if (state != GameState::InProgress)
		{
			throw IllegalStateException("Game Over");
		}

		if (word.find(c) == std::string::npos)
		{
			fail(c);
			return;
		}

		success(c);
	}

	void Hangman::render(ostream& output)
	{
		renderTitle(output);

		output << " ______"  << endl
			   << "   " << this->misses[0].print() << "   \\" << endl
			   << "   " << this->misses[1].print() << "   |" << endl
			   << " " << this->misses[2].print() << this->misses[3].print() << this->misses[4].print() << " |" << endl
			   << "  " << this->misses[5].print() << " " << this->misses[6].print() << "  |" << endl
			   << " ______|" << endl
			   << result << endl;
			   
		std::vector<char> activeMisses;

		for (Miss m : this->misses)
		{
			if (!m.isActive())
			{
				break;
			}

			activeMisses.push_back(m.value());
		}
		
		output << "Misses: " << Utilities::join(' ', activeMisses) << std::endl;

		if (state == GameState::Win)
		{
			output << "You win! :D";
			return;
		}
		
		if (state == GameState::Loss)
		{
			output << "You've been hanged... :(" << std::endl
			       << "The word was: " << word;
			return;
		}
	}

	bool Hangman::isInProgress()
	{
		return state == GameState::InProgress;
	}

	void Hangman::fail(char c)
	{
		misses[this->guesses].value(c);
		this->guesses++;

		if (this->guesses == misses.size())
		{
			state = GameState::Loss;
		}
	}

	void Hangman::success(char c)
	{
		for (int i = 0; i < word.size(); ++i)
		{
			if (word[i] == c)
			{
				result[i] = c;
			}
		}

		if (result.find(UNKNOWN_CHAR) == string::npos)
		{
			state = GameState::Win;
		}
	}

	void Hangman::loadMisses()
	{
		this->misses.push_back(Miss("|"));
		this->misses.push_back(Miss("o"));
		this->misses.push_back(Miss("--"));
		this->misses.push_back(Miss("|"));
		this->misses.push_back(Miss("--"));
		this->misses.push_back(Miss("/"));
		this->misses.push_back(Miss("\\"));
	}

	void Hangman::renderTitle(std::ostream& output)
	{
		const int TITLE_LENGTH = 80;
		string border(TITLE_LENGTH, '=');
		string title("HANGMAN");

		output << border << std::endl
			   << "| " << title.append(TITLE_LENGTH - 2 - title.length(), ' ') << "|" << std::endl
			   << border << std::endl;
	}
}