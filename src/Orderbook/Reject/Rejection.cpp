#include "TradingEngine/Orderbook/Reject/Rejection.h"

namespace TradingEngine::Orderbook::Reject {
	rejectionReason Rejection::getRejectionReason()
	{
		return rr_;
	}

	long Rejection::getRejectedOrderId()
	{
		return roid_;
	}

	Rejection::Rejection(long roid, rejectionReason rr)
		: roid_(roid), rr_(rr) {}
}
