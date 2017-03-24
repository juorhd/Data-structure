void lookup( COSTUME_SHOP_TYPE& costume_shop) {
  string costume_name;
  cin >> costume_name;

  int index = -1;
  for ( int i=0; i<costume_shop.size(); ++i )
    if (costume_shop[i].first == costume_name) {
     index = i;
     break;
  }
  if ( index == -1 ) cout << "The shop doesn't carry " << costume_name << " costumes.\n";
  else {
      cout << "Shop info for " << costume_name << " costumes:\n";
      if ( costume_shop[index].second.first != 0 ){
        int costum_num = costume_shop[index].second.first;
        cout << "  " << costum_num << " cop" << ( costum_num>1 ? "ies" : "y" ) << " available\n";
      }
      if ( costume_shop[index].second.second.size() != 0 ){
        int people_num = costume_shop[index].second.second.size();
        cout << "  " << people_num <<  " cop" << ( people_num>1 ? "ies" : "y" ) << " rented by:\n";
        for (int i=0; i<people_num; ++i)
          cout << "    " << costume_shop[index].second.second[i].getfirstname() << ' '
             << costume_shop[index].second.second[i].getlastname() << endl;
      }
  }
}