#pragma once

#include <IcuUtil.h>
#include <ILexStream.h>
#include <ParseErrorCodes.h>
#include <LibLsp/lsp/textDocument/publishDiagnostics.h>
#include "IMessageHandler.h"
enum
{
    MACRO_EXPECTED_INSTEAD_OF_SYMBOL = ParseErrorCodes::MANUAL_CODE + 1,
    SYMBOL_EXPECTED_INSTEAD_OF_MACRO,
    RESPECIFICATION_OF_ERROR_SYMBOL,
    RESPECIFICATION_OF_IDENTIFIER_SYMBOL,
    RESPECIFICATION_OF_EOL_SYMBOL,
    RESPECIFICATION_OF_EOF_SYMBOL,
    RESPECIFICATION_OF_START_SYMBOL,
    RECURSIVE_IMPORT
};

struct ProblemHandler : public IMessageHandler
{
	Notify_TextDocumentPublishDiagnostics::notify notify;
	lsRange toRange(const Location& location);

	void handleMessage(int errorCode, const Location& msgLocation, const Location& errorLocation,
	                   const std::wstring& filename, const std::vector<std::wstring>& errorInfo) override;

	void handleMessage(const lsDiagnosticSeverity severity, IToken* left, IToken* right,  Tuple<const char*>& msg);
};

