#include <eosiolib/asset.hpp>
#include "addressbook.hpp"
using namespace eosio;

 ACTION addressbook::add( name account, string name, uint8_t age,  uint64_t phonenumber, string address ) {
   require_auth( account );
   addressbooks_t addressbooks(_self,  account.value);
   addressbooks.emplace(account,
                        [&]( auto& row ){
                           row.id          = addressbooks.available_primary_key();
                           row.name        = name;
                           row.age         = age;              
                           row.phonenumber = phonenumber;         
                           row.address     = address;               
                        }
                     ); 
//  eosio::action( permission_level{_self, eosio::name("active")},_self, eosio::name("remove"), std::make_tuple(_self, 0)).send();
//  SEND_INLINE_ACTION( *this, remove, { {_self, eosio::name("active")} },
//                       { _self, 2 }
//   );
}

ACTION addressbook::remove(name account, uint64_t id) {
   require_auth(account);
   addressbooks_t addressbooks(_self, account.value);  
   auto itr = addressbooks.find(id);
   addressbooks.erase(itr);
}

ACTION addressbook::update(name account, uint64_t id, string name, uint8_t age,  uint64_t phonenumber, string address) {
   require_auth(account);
   addressbooks_t addressbooks(_self, account.value);  
   auto itr = addressbooks.find(id);
   //name a= string_to_name("bob");
   addressbooks.modify( itr, 
                        account,
                        [&]( auto& row ){
                           row.name        = name;              
                           row.age         = age;              
                           row.phonenumber = phonenumber;         
                           row.address     = address;               
                        }
               );  
}


ACTION addressbook::clean( name account, int32_t batch_size) {
	require_auth(account);

	if(batch_size == 0)
		batch_size =  1000;

	int32_t count=0;
	addressbooks_t addressbooks(_self, account.value);
	auto itr = addressbooks.begin();
	auto end = addressbooks.end();
	while(itr != end) {
	   itr = addressbooks.erase(itr);
	   count++;
	   if(batch_size < 0)
		   continue;
	   if(count >= batch_size)
		   break;
	}
}

EOSIO_DISPATCH( addressbook, (add)(remove)(update)(clean) )


/*

cl push action addressbook add '["zhanghan", "zhangsan", 18, 13811094444,  "北京“]'

*/

