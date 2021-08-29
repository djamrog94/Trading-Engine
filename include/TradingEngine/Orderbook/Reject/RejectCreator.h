#pragma once
#include "TradingEngine/Orderbook/Reject/Rejection.h"
#include "TradingEngine/Orders/ModifyOrder.h"

namespace TradingEngine::Orderbook::Reject {
	class RejectCreator
	{
		static Rejection generateModyifyRejection(Orders::ModifyOrder mo, Reject::rejectionReason rr);
	};
}

