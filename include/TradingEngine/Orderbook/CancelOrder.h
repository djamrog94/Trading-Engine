#pragma once
#include "TradingEngine/Orderbook/OrderCore.h"
#include "TradingEngine/Orderbook/ModifyOrder.h"
#include <string>

namespace TradingEngine::Orderbook {
	class CancelOrder : public OrderCore
	{
	public:
		CancelOrder(OrderCore& orderBase);

		CancelOrder(ModifyOrder& modifyOrder);

	private:
		OrderCore orderBase_;
	};
}
