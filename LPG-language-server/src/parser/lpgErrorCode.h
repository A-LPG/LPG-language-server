#pragma once

#include <IcuUtil.h>
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
	lsRange toRange(const Location& location)
	{
		lsRange range;
		range.start.line = location.start_line - 1;
		range.start.character = location.start_column;
		range.end.line = location.end_line - 1;
		range.end.character = location.end_column;
		return  range;
	}
	void handleMessage(int errorCode, const Location& msgLocation, const Location& errorLocation,
		const std::wstring& filename, const std::vector<std::wstring>& errorInfo) override
	{
		lsDiagnostic diagnostic;
		diagnostic.severity = lsDiagnosticSeverity::Error;
		diagnostic.range = toRange(msgLocation);
		std::string info;
		for (auto& it : errorInfo)
		{
			info += IcuUtil::ws2s(it);
			info += "\n";
		}
		diagnostic.message.swap(info);
		notify.params.diagnostics.emplace_back(std::move(diagnostic));
	}
	void handleMessage(const lsDiagnosticSeverity severity, IToken*, IToken*, const Tuple<const char*>& msg)
	{
		
	}
};