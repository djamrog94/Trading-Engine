#pragma once
#include "TradingEngine/Orders/Order.h"
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Orderbook/Reject/Rejection.h"
#include "TradingEngine/Orderbook/Reject/RejectCreator.h"
namespace TradingEngine::Orderbook {
	class RejectGenerator
	{
	public:
		bool tryRejectNewOrder(Orders::Order order, RetrievalOrderbook orderbook, Orderbook::Reject::Rejection& rejection);
		bool tryRejectModifyOrder(Orders::ModifyOrder modifyOrder, RetrievalOrderbook orderbook, Orderbook::Reject::Rejection& rejection);
		bool tryRejectCancelOrder(Orders::CancelOrder cancelOrder, RetrievalOrderbook orderbook, Orderbook::Reject::Rejection& rejection);
	};
}
