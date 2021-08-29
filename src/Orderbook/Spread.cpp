#include "TradingEngine/Orderbook/Spread.h"

namespace TradingEngine::Orderbook {
	Spread::Spread(long bid, long ask): bid_(bid), ask_(ask)
	{
	}
	long Spread::getBid()
	{
		return bid_;
	}
	long Spread::getAsk()
	{
		return ask_;
	}
}
