#include "Utilities.h"
#include "Hangman.h"

using namespace Utilities;

namespace HangmanGame
{
	class GameState
	{
		protected:
			Hangman* game;

			GameState(Hangman* game)
			{
				this->game = game;
			}

		public:
			virtual void guess(char c)
			{
				throw IllegalStateException("Game Over");
			}

			virtual bool isInProgress()
			{
				return false;
			}


	};
}