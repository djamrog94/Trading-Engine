#include "TradingEngine/Orderbook/OrderbookFactory.h"
namespace TradingEngine::Orderbook {
	MatchingOrderbook TradingEngine::Orderbook::OrderbookFactory::createOrderbook(Instrument::Security inst)
	{
		std::unique_ptr algo = std::make_unique < MatchingAlgorithm::MatchingAlgorithm > ();
		std::unique_ptr ob = std::make_unique<RetrievalOrderbook>();
		return MatchingOrderbook(std::move(ob), std::move(algo));
	}
}
