#pragma once
#include "TradingEngine/Orderbook/OrderStatuses/CancelOrderStatus.h"
#include "TradingEngine/Orderbook/OrderStatuses/NewOrderStatus.h"
#include "TradingEngine/Orderbook/OrderStatuses/ModifyOrderStatus.h"
#include "TradingEngine/Orders/CancelOrder.h"
#include "TradingEngine/Orders/Order.h"
#include "TradingEngine/Orders/ModifyOrder.h"

namespace TradingEngine::Orderbook {
	class ActionResultConversion
	{
	public:
		static OrderStatuses::CancelOrderStatus generateCancelOrderStatus(Orders::CancelOrder obe);
		static OrderStatuses::NewOrderStatus generateNewOrderStatus(Orders::Order obe);
		static OrderStatuses::ModifyOrderStatus generateModifyOrderStatus(Orders::ModifyOrder obe);
	};
}

