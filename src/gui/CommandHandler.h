/*
* TzarRemake
* Copyright (C) 2018
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

//--------------------------------------------------------------------------

namespace gui
{

	class CommandHandler;

	/*!
	* \brief Class which holds all information about message
	*/
	class CommandArgs
	{
	public:
		/*!
		*	\brief Structure holding 2 int values
		*/
		struct Vector2i
		{
			int x;
			int y;
		};

		/*!
		*	\brief Structure holding 4 int values
		*/
		struct Vector4i
		{
			int x1;
			int y1;
			int x2;
			int y2;
		};

		/*!
		* \brief Specify all possible messages types for widgets
		*/
		enum class CommandType
		{
			startHover,	///< start hovering widget		
			stopHover,	///< stop hovering widget
			startClick,	///< start click widget
			stopClick,	///< stop click widget
			click,		///< click widget
			textEntered,///< entered text
		};

		CommandType type;			///< specify message type of the object

		/*!
		* \brief This union specify additional message information
		*/
		union
		{
			char character;					///< character
			unsigned int unicodeCharacter;	///< unicode character
		};

	};

	/*!
	* \brief This class is used to send commands
	*/
	class GuiCommand
	{
	public:
		GuiCommand() = default;
		~GuiCommand() noexcept {}
		GuiCommand(const GuiCommand &) = delete;
		GuiCommand(GuiCommand &&) = delete;
		GuiCommand & operator=(GuiCommand &) = delete;
		GuiCommand & operator=(GuiCommand &&) = delete;

		/*!
		* \brief Sends command to receiver
		*/
		void operator()(CommandHandler * const  sender, CommandHandler * const receiver);

		/*!
		* \brief Sends command to receiver
		*/
		void send(CommandHandler * const  sender, CommandHandler * const receiver);

		CommandArgs args;	///< Command Arguments used in recent call
	};

	/*!
	* \brief Class for handling commands
	*/
	class CommandHandler
	{
	public:
		CommandHandler() = default;
		~CommandHandler() noexcept {}

		/*!
		* \brief Handle all received commands
		*/
		virtual void handleCommand(CommandHandler * const sender, const CommandArgs  & args) = 0;


	protected:
		GuiCommand commander; ///< Object of class which handle sending commands
	};
}

/*!
* \class gui::CommandHandler
*
* gui::CommandHandler is abstract class which handle command driven programming technique.
* Command is send from one object to one or multiple other objects. In command driven programming, sender
* specify which objects will get the command message.
* Any class which wants to send or receive commands should derive from this class.
*
*/