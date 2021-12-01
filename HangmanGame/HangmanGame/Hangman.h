#pragma once

#include <string>
#include <vector>

namespace HangmanGame
{
	enum class GameState { InProgress, Win, Loss };

	class Miss final
	{
		char val;
		std::string bPart;
		std::string empty;

		public:
			Miss(std::string);
			char value();
			void value(char);
			std::string print();
			bool isActive();
	};

	class Hangman final
	{
		static const char UNKNOWN_CHAR = '-';

		std::string word;
		std::string result;
		std::vector<Miss> misses;
		size_t guesses;
		GameState state;

		public:
			Hangman(std::string);
			void guess(char);
			void render(std::ostream&);
			bool isInProgress();
			
		private:
			void fail(char);
			void success(char);
			void renderTitle(std::ostream&);
			void loadMisses();
	};
}

