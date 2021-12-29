#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include <stack>
#include <boost/asio/basic_signal_set.hpp>

namespace
{

	#define GetRValue(rgb)      (LOBYTE(rgb))
	#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
	#define GetBValue(rgb)      (LOBYTE((rgb)>>16))
	struct SWT
	{
		/**
	 * Default color white (value is 1).
	 */
		const static  int COLOR_WHITE = 1;

		/**
		 * Default color black (value is 2).
		 */
		const static  int COLOR_BLACK = 2;

		/**
		 * Default color red (value is 3).
		 */
		const static  int COLOR_RED = 3;

		/**
		 * Default color dark red (value is 4).
		 */
		const static  int COLOR_DARK_RED = 4;

		/**
		 * Default color green (value is 5).
		 */
		const static  int COLOR_GREEN = 5;

		/**
		 * Default color dark green (value is 6).
		 */
		const static  int COLOR_DARK_GREEN = 6;

		/**
		 * Default color yellow (value is 7).
		 */
		const static  int COLOR_YELLOW = 7;

		/**
		 * Default color dark yellow (value is 8).
		 */
		const static  int COLOR_DARK_YELLOW = 8;

		/**
		 * Default color blue (value is 9).
		 */
		const static  int COLOR_BLUE = 9;

		/**
		 * Default color dark blue (value is 10).
		 */
		const static  int COLOR_DARK_BLUE = 10;

		/**
		 * Default color magenta (value is 11).
		 */
		const static  int COLOR_MAGENTA = 11;

		/**
		 * Default color dark magenta (value is 12).
		 */
		const static  int COLOR_DARK_MAGENTA = 12;

		/**
		 * Default color cyan (value is 13).
		 */
		const static  int COLOR_CYAN = 13;

		/**
		 * Default color dark cyan (value is 14).
		 */
		const static  int COLOR_DARK_CYAN = 14;

		/**
		 * Default color gray (value is 15).
		 */
		const static  int COLOR_GRAY = 15;

		/**
		 * Default color dark gray (value is 16).
		 */
		const static  int COLOR_DARK_GRAY = 16;

		/*
		 * System Colors
		 *
		 * Dealing with system colors is an area where there are
		 * many platform differences.  On some platforms, system
		 * colors can change dynamically while the program is
		 * running.  On other platforms, system colors can be
		 * changed for all instances of a particular widget.
		 * Therefore, the only truly portable method to obtain
		 * a widget color query is to query the color from an
		 * instance of the widget.
		 *
		 *	It is expected that the list of supported colors
		 * will grow over time.
		 */

		 /**
		  * System color used to paint dark shadow areas (value is 17).
		  */
		const static  int COLOR_WIDGET_DARK_SHADOW = 17;

		/**
		 * System color used to paint normal shadow areas (value is 18).
		 */
		const static  int COLOR_WIDGET_NORMAL_SHADOW = 18;

		/**
		 * System color used to paint light shadow areas (value is 19).
		 */
		const static  int COLOR_WIDGET_LIGHT_SHADOW = 19;

		/**
		 * System color used to paint highlight shadow areas (value is 20).
		 */
		const static  int COLOR_WIDGET_HIGHLIGHT_SHADOW = 20;

		/**
		 * System color used to paint foreground areas (value is 21).
		 */
		const static  int COLOR_WIDGET_FOREGROUND = 21;

		/**
		 * System color used to paint background areas (value is 22).
		 */
		const static  int COLOR_WIDGET_BACKGROUND = 22;

		/**
		 * System color used to paint border areas (value is 23).
		 */
		const static  int COLOR_WIDGET_BORDER = 23;

		/**
		 * System color used to paint list foreground areas (value is 24).
		 */
		const static  int COLOR_LIST_FOREGROUND = 24;

		/**
		 * System color used to paint list background areas (value is 25).
		 */
		const static  int COLOR_LIST_BACKGROUND = 25;

		/**
		 * System color used to paint list selection background areas (value is 26).
		 */
		const static  int COLOR_LIST_SELECTION = 26;

		/**
		 * System color used to paint list selected text (value is 27).
		 */
		const static  int COLOR_LIST_SELECTION_TEXT = 27;

		/**
		 * System color used to paint tooltip text (value is 28).
		 */
		const static  int COLOR_INFO_FOREGROUND = 28;

		/**
		 * System color used to paint tooltip background areas (value is 29).
		 */
		const static  int COLOR_INFO_BACKGROUND = 29;

		/**
		 * System color used to paint title text (value is 30).
		 */
		const static  int COLOR_TITLE_FOREGROUND = 30;

		/**
		 * System color used to paint title background areas (value is 31).
		 */
		const static  int COLOR_TITLE_BACKGROUND = 31;

		/**
		 * System color used to paint title background gradient (value is 32).
		 */
		const static  int COLOR_TITLE_BACKGROUND_GRADIENT = 32;

		/**
		 * System color used to paint inactive title text (value is 33).
		 */
		const static  int COLOR_TITLE_INACTIVE_FOREGROUND = 33;

		/**
		 * System color used to paint inactive title background areas (value is 34).
		 */
		const static  int COLOR_TITLE_INACTIVE_BACKGROUND = 34;

		/**
		 * System color used to paint inactive title background gradient (value is 35).
		 */
		const static  int COLOR_TITLE_INACTIVE_BACKGROUND_GRADIENT = 35;

		/**
		 * System color used to paint link text (value is 36).
		 *
		 * @since 3.102
		 */
		const static  int COLOR_LINK_FOREGROUND = 36;

		/**
		 * System color used to paint with alpha 0 (value is 37).
		 * <p>
		 * This pseudo-color can be used to set a transparent background on SWT
		 * controls. <br>
		 * Note that this is a <em>HINT</em> and may be overridden by the platform.
		 * For example:
		 * <ul>
		 * <li>{@link org.eclipse.swt.widgets.Combo Combo},
		 * {@link org.eclipse.swt.widgets.List List} and
		 * {@link org.eclipse.swt.widgets.Tree Tree} support transparent background
		 * on GTK3 and Windows only.</li>
		 * <li>{@link org.eclipse.swt.widgets.Text Text} supports transparent
		 * background on Windows only whereas {@link org.eclipse.swt.widgets.Table
		 * Table} supports transparent background on GTK3 only.</li>
		 * </ul>
		 *
		 * @since 3.104
		 */
		const static  int COLOR_TRANSPARENT = 37;

		/**
		 * System color used to paint disabled text background areas (value is 38).
		 *
		 * @since 3.112
		 */
		const static  int COLOR_TEXT_DISABLED_BACKGROUND = 38;

		/**
		 * System color used to paint disabled foreground areas (value is 39).
		 *
		 * @since 3.112
		 */
		const static  int COLOR_WIDGET_DISABLED_FOREGROUND = 39;
	};

	struct Color
	{
		int handle = 0;
		int alpha = 255;

		TextDocument::Color Convert() const
		{
			TextDocument::Color _color;
			_color.alpha = alpha / 255.0;
#if _WIN32
			_color.red =  GetRValue(handle)/255.0;
			_color.green = GetGValue(handle) / 255.0;
			_color.blue = GetBValue(handle) / 255.0;
#endif
			return  _color;
		}
		static Color win32_new(int handle, int alpha) {
			Color color;
			color.handle = handle;
			color.alpha = alpha;
			return color;
		}
		static Color win32_new(int handle)
		{
			return  win32_new(handle, 255);
		}
	
		static Color getSystemColor(int id) {
			
			int pixel = 0x00000000;
#if _WIN32
			switch (id) {
			case SWT::COLOR_WIDGET_DARK_SHADOW:		pixel = ::GetSysColor(COLOR_3DDKSHADOW);	break;
			case SWT::COLOR_WIDGET_DISABLED_FOREGROUND: pixel = ::GetSysColor(COLOR_GRAYTEXT); break;
			case SWT::COLOR_WIDGET_NORMAL_SHADOW:	pixel = ::GetSysColor(COLOR_3DSHADOW); 	break;
			case SWT::COLOR_WIDGET_LIGHT_SHADOW: 	pixel = ::GetSysColor(COLOR_3DLIGHT);  	break;
			case SWT::COLOR_WIDGET_HIGHLIGHT_SHADOW:	pixel = ::GetSysColor(COLOR_3DHIGHLIGHT);  break;
			case SWT::COLOR_TEXT_DISABLED_BACKGROUND:
			case SWT::COLOR_WIDGET_BACKGROUND: 		pixel = ::GetSysColor(COLOR_3DFACE);  	break;
			case SWT::COLOR_WIDGET_BORDER: 		pixel = ::GetSysColor(COLOR_WINDOWFRAME);  break;
			case SWT::COLOR_WIDGET_FOREGROUND:
			case SWT::COLOR_LIST_FOREGROUND: 		pixel = ::GetSysColor(COLOR_WINDOWTEXT);	break;
			case SWT::COLOR_LIST_BACKGROUND: 		pixel = ::GetSysColor(COLOR_WINDOW);  	break;
			case SWT::COLOR_LIST_SELECTION: 		pixel = ::GetSysColor(COLOR_HIGHLIGHT);	break;
			case SWT::COLOR_LIST_SELECTION_TEXT: 	pixel = ::GetSysColor(COLOR_HIGHLIGHTTEXT); break;
			case SWT::COLOR_LINK_FOREGROUND: 	pixel = ::GetSysColor(COLOR_HOTLIGHT); break;
			case SWT::COLOR_INFO_FOREGROUND:		pixel = ::GetSysColor(COLOR_INFOTEXT);	break;
			case SWT::COLOR_INFO_BACKGROUND:		pixel = ::GetSysColor(COLOR_INFOBK);		break;
			case SWT::COLOR_TITLE_FOREGROUND: 		pixel = ::GetSysColor(COLOR_CAPTIONTEXT);	break;
			case SWT::COLOR_TITLE_BACKGROUND:		pixel = ::GetSysColor(COLOR_ACTIVECAPTION);		break;
			case SWT::COLOR_TITLE_BACKGROUND_GRADIENT:
				pixel = ::GetSysColor(COLOR_GRADIENTACTIVECAPTION);
				if (pixel == 0) pixel = ::GetSysColor(COLOR_ACTIVECAPTION);
				break;
			case SWT::COLOR_TITLE_INACTIVE_FOREGROUND: 		pixel = ::GetSysColor(COLOR_INACTIVECAPTIONTEXT);	break;
			case SWT::COLOR_TITLE_INACTIVE_BACKGROUND:			pixel = ::GetSysColor(COLOR_INACTIVECAPTION);		break;
			case SWT::COLOR_TITLE_INACTIVE_BACKGROUND_GRADIENT:
				pixel = ::GetSysColor(COLOR_GRADIENTINACTIVECAPTION);
				if (pixel == 0) pixel = ::GetSysColor(COLOR_INACTIVECAPTION);
				break;
			default:
				return getSystemColorInternal(id);
			}
#endif

			return win32_new( pixel);
		}
	private:
		static Color getSystemColorInternal(int id) {

			int pixel = 0x00000000;
			int alpha = 255;
			switch (id) {
			case SWT::COLOR_TRANSPARENT:			alpha = 0;  break;
			case SWT::COLOR_WHITE:				pixel = 0x00FFFFFF;  break;
			case SWT::COLOR_BLACK:				pixel = 0x00000000;  break;
			case SWT::COLOR_RED:					pixel = 0x000000FF;  break;
			case SWT::COLOR_DARK_RED:			pixel = 0x00000080;  break;
			case SWT::COLOR_GREEN:				pixel = 0x0000FF00;  break;
			case SWT::COLOR_DARK_GREEN:			pixel = 0x00008000;  break;
			case SWT::COLOR_YELLOW:				pixel = 0x0000FFFF;  break;
			case SWT::COLOR_DARK_YELLOW:		pixel = 0x00008080;  break;
			case SWT::COLOR_BLUE:				pixel = 0x00FF0000;  break;
			case SWT::COLOR_DARK_BLUE:			pixel = 0x00800000;  break;
			case SWT::COLOR_MAGENTA:			pixel = 0x00FF00FF;  break;
			case SWT::COLOR_DARK_MAGENTA:		pixel = 0x00800080;  break;
			case SWT::COLOR_CYAN:				pixel = 0x00FFFF00;  break;
			case SWT::COLOR_DARK_CYAN:			pixel = 0x00808000;  break;
			case SWT::COLOR_GRAY:				pixel = 0x00C0C0C0;  break;
			case SWT::COLOR_DARK_GRAY:			pixel = 0x00808080;  break;
			default: ;
			}
			return win32_new(pixel, alpha);
		}
	
	};



	TextDocument::Color COMMENT = Color::getSystemColor(SWT::COLOR_DARK_CYAN).Convert();
	
	TextDocument::Color SYMBOL = Color::getSystemColor(SWT::COLOR_DARK_RED).Convert();
	
	TextDocument::Color KEYWORD = Color::getSystemColor(SWT::COLOR_BLUE).Convert();
	
	TextDocument::Color LITERAL = Color::getSystemColor(SWT::COLOR_DARK_GRAY).Convert();
	
	TextDocument::Color EMPTY = Color::getSystemColor(SWT::COLOR_DARK_GRAY).Convert();
	
	TextDocument::Color ANNOTATION = Color::getSystemColor(SWT::COLOR_MAGENTA).Convert();

	TextDocument::Color Other = Color::getSystemColor(SWT::COLOR_BLACK).Convert();

	

}
struct DocumentColorHandlerData
{
	std::shared_ptr<CompilationUnit>& unit;
	
	shared_ptr_wstring buffer;
	DocumentColorHandlerData(std::shared_ptr<CompilationUnit>& u, std::vector<ColorInformation>& o) :unit(u)
	{
		if (!unit)
		{
			return;
		}
		Init();
		auto lex = unit->runtime_unit->_lexer.getILexStream();
		auto process_token = [&](IToken* token)
		{
			ColorInformation information;
			information.color = getColoring(token);

			auto pos = ASTUtils::toPosition(lex, token->getStartOffset());
			if (pos)
			{
				information.range.start = pos.value();
			}
			pos = ASTUtils::toPosition(lex, token->getEndOffset());
			if (pos)
			{
				information.range.end = pos.value();
			}
			o.emplace_back(information);
		};
		{
			Tuple<IToken*>& tokens = u->runtime_unit->_parser.prsStream->tokens;
			for (int i = 0; i < tokens.size(); ++i)
			{
				IToken* token = tokens[i];
				process_token(token);
			}
		}
		{
			Tuple<IToken*>& tokens = u->runtime_unit->_parser.prsStream->adjuncts;
			for (int i = 0; i < tokens.size(); ++i)
			{
				IToken* token = tokens[i];
				process_token(token);
			}
		}
	}
	void Init()
	{
		auto& parser = unit->runtime_unit->_parser;
		auto  tokenKindNames = parser.orderedTerminalSymbols();
		fIsKeyword.resize(tokenKindNames.size());

		auto keywordKinds = unit->runtime_unit->_lexer.kwLexer->keywordKind;
		auto length = unit->runtime_unit->_lexer.kwLexer->keywordKindLenth;
		for (int i = 1; i < length; i++) {
			int index = parser.getIPrsStream()->mapKind(keywordKinds[i]);
			fIsKeyword[index] = true;

		}
		buffer = unit->runtime_unit->_parser.getIPrsStream()->getInputChars();
	}
	std::vector<bool>fIsKeyword;
	bool isKeyword(int kind) {
		return kind < LPGParsersym::numTokenKinds&& fIsKeyword[kind];
	}
	TextDocument::Color getColoring(IToken* token) {

		auto kind = token->getKind();
		if (kind == LPGParsersym::TK_EMPTY_KEY)
			return EMPTY;
		if (isKeyword(token->getKind()))
			return KEYWORD;
		if (kind == LPGParsersym::TK_SYMBOL)
		{
			int tokStartOffset = token->getStartOffset();
			wchar_t ch = buffer[tokStartOffset];
			if (ch == '\'' || ch == '"')
				return LITERAL;
			return SYMBOL;
		}
		if (kind == LPGParsersym::TK_SINGLE_LINE_COMMENT)
			return COMMENT;
		if (kind == LPGParsersym::TK_MACRO_NAME)
			return ANNOTATION;

		return Other;
	}

};
DocumentColorHandler::DocumentColorHandler(std::shared_ptr<CompilationUnit>&u, std::vector<ColorInformation>&o) :d_ptr(new DocumentColorHandlerData(u,o))
{

}

DocumentColorHandler::~DocumentColorHandler()
{
	delete d_ptr;
}
