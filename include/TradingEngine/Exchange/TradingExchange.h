#pragma once
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Instrument/Security.h"
#include <string>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include "TradingEngine/Orderbook/MatchingOrderBook.h"
#include "TradingEngine/Orderbook/OrderbookFactory.h"

namespace TradingEngine::Exchange {
	class TradingExchange
	{
	public:
		TradingExchange(std::string yaml_file_path);
		int getExchangeId();
		std::string getExchangeName();
		bool tryGetOrderbook(Instrument::Security security, Orderbook::RetrievalOrderbook& orderbook);
	private:
		int exchangeId_;
		std::string exchangeName_;
		YAML::Node config_;
		std::map<int, Orderbook::MatchingOrderbook> orderbooks_;

	};
}

