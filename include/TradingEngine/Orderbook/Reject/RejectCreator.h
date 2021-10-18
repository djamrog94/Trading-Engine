#pragma once
#include "TradingEngine/Orderbook/Reject/Rejection.h"
#include "TradingEngine/Orders/ModifyOrder.h"

namespace TradingEngine::Orderbook::Reject {
	class RejectCreator
	{
	public:
		static Rejection generateOrderCoreReject(Orders::OrderCore oc, Reject::rejectionReason rr);
	};
}

