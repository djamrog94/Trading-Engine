#pragma once
#include "TradingEngine/Orders/OrderCore.h"

namespace TradingEngine::Orders {
	class ModifyOrder : public OrderCore
	{
	public:
		ModifyOrder(OrderCore& orderBase, long price, uint16_t modifyQuantity, bool isBuySide);

		long getPrice();
		uint16_t getQuantity();
		bool getIsBuySide();
		OrderCore getCore();

		//CancelOrder toCancelOrder();
		//Order toNewOrder();

		long price_;
		uint16_t modifyQuantity_;
		bool isBuySide_;

	private:
		
		OrderCore orderBase_;


	};
}
