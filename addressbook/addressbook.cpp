#include "addressbook.hpp"
#include <eosiolib/asset.hpp>
using namespace eosio;

 ACTION addressbook::add( name account, string name, uint8_t age,  uint64_t phonenumber, string address ) {
   require_auth( account );
   addressbooks_t addressbooks(_self, account.value);
   addressbooks.emplace(   _self,
                        [&]( auto& row ){
                           row.id          = addressbooks.available_primary_key();
                           row.name        = name;              
                           row.age         = age;              
                           row.phonenumber = phonenumber;         
                           row.address     = address;               
                        }
                     ); 
}

ACTION addressbook::remove(name account, uint64_t id) {
   require_auth(account);
   addressbooks_t addressbooks(_self, account.value);  
   auto itr = addressbooks.find(id);
   addressbooks.erase(itr);
}

EOSIO_DISPATCH( addressbook, (add)(remove) ) 

