#pragma once
#include <string>
#include <iostream>
namespace TradingEngine::Orderbook {
	class OrderCore
	{
	public:
		OrderCore();

		OrderCore(long orderId, std::string username, int securityID);

		long getOrderId() const;
		std::string getUsername() const;
		int getSecurityId() const;
		static OrderCore createOrderCore(long orderId, std::string username, int securityId);
		std::string toString();

	private:
		long orderId_;
		std::string username_;
		int securityID_;
	};


	std::ostream& operator << (std::ostream& outs, const OrderCore& oc);
}
