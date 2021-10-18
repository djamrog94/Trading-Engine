#include "TradingEngine/Orderbook/Reject/Rejection.h"

namespace TradingEngine::Orderbook::Reject {
	rejectionReason Rejection::getRejectionReason()
	{
		return rr_;
	}

	Orders::OrderCore Rejection::getOrderCore()
	{
		return orderBase_;
	}


	Rejection::Rejection(Orders::OrderCore rejectedOrder, rejectionReason rr)
		: orderBase_(rejectedOrder), rr_(rr) {}
}
