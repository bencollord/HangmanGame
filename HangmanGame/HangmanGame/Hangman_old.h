#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Utilities.h"

namespace Old
{
	enum class GameState { InProgress, Win, Loss };

	class Hangman final
	{
		static const unsigned int MAX_TRIES = 8;
		static const char UNKNOWN_CHAR = '-';

		std::string word;
		std::string result;
		std::vector<char> misses;
		GameState gameState = GameState::InProgress;

	public:
		Hangman(std::string word)
		{
			this->word = word;
			this->result.resize(this->word.size());

			for (int i = 0; i < this->word.size(); ++i)
			{
				this->result[i] = isblank(this->word[i]) ? this->word[i] : UNKNOWN_CHAR;
			}
		}

		GameState state()
		{
			return this->gameState;
		}

		void guess(char c)
		{
			if (gameState != GameState::InProgress)
			{
				throw Utilities::IllegalStateException("Game Over");
			}

			if (word.find(c) == std::string::npos)
			{
				fail(c);
				return;
			}

			success(c);
		}

		void render(std::ostream& output)
		{
			renderTitle(output);

			if (gameState == GameState::Win)
			{
				output << "You win! :D";
				return;
			}

			if (gameState == GameState::Loss)
			{
				output << "You lose... :(" << std::endl
					<< "The word was: " << word;
				return;
			}

			output << result << std::endl
				<< "Guesses left: " << MAX_TRIES - misses.size() << std::endl
				<< "Misses: " << Utilities::join(' ', misses) << std::endl;

			/*output << " ____  " << endl
				   << "  " << "  " << noose << "  \\ " << endl
				<< "  " << head << "  | " << endl
				<< " " << leftArm << body << rightArm << " | " << endl
				<< " " << leftLeg << " " << rightLeg << " | " << endl
				<< " ____| " << endl;*/

			output << Utilities::repeat("\n", 100);
		}

	private:
		void fail(char c)
		{
			misses.push_back(c);

			if (misses.size() == MAX_TRIES)
			{
				gameState = GameState::Loss;
			}
		}

		void success(char c)
		{
			for (int i = 0; i < word.size(); ++i)
			{
				if (word[i] == c)
				{
					result[i] = c;
				}
			}

			if (result.find(UNKNOWN_CHAR) == std::string::npos)
			{
				gameState = GameState::Win;
			}
		}

		void renderTitle(std::ostream& output)
		{
			const int TITLE_LENGTH = 80;
			std::string border(TITLE_LENGTH, '=');
			std::string title("HANGMAN");

			output << border << std::endl
				<< "| " << title.append(TITLE_LENGTH + 2 - title.length(), ' ') << "|" << std::endl
				<< border << std::endl;
		}
	};
}