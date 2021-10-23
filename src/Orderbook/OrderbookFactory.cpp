#include "TradingEngine/Orderbook/OrderbookFactory.h"
namespace TradingEngine::Orderbook {
	MatchingOrderbook TradingEngine::Orderbook::OrderbookFactory::createOrderbook(Instrument::Security inst)
	{
		std::unique_ptr algo = std::make_unique < MatchingAlgorithm::FifoMatchingAlgorithm > ();
		std::unique_ptr ob = std::make_unique<Orderbook>(Instrument::Security());
		return MatchingOrderbook(std::move(ob), std::move(algo));
	}
}
