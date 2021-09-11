#include "TradingEngine/Instrument/Security.h"
namespace TradingEngine::Instrument {
	Security::Security() = default;
	TradingEngine::Instrument::Security::Security(int securityId, std::string symbol, Orderbook::FillAllocationAlgorithm allocAlgo)
		: securityId_(securityId), symbol_(symbol), allocAlgo_(allocAlgo) {}
}
