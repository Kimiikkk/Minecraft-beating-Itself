import json,sys
p=sys.argv[1] if len(sys.argv)>1 else 'replay.jsonl'
e=[]
with open(p,encoding='utf-8') as f:
 for line in f:
  try:
   o=json.loads(line)
   if o.get('kind')=='event': e.append(o)
  except: pass
first=lambda t: next((x for x in e if x['type']==t),None)
last=lambda t: next((x for x in reversed(e) if x['type']==t),None)
print('=== MINECRAFT SELF-BEATING REPLAY SUMMARY ===')
for t,label in [('pumpkin_picked','First pumpkin picked'),('nearest_outpost_located','Nearest outpost identified'),('creeper_explosion','First explosion'),('route_opened','Route opened'),('portal_reached','End Portal first reached'),('end_entered','First End entry'),('snow_golem_entered_end','First Snow Golem in End'),('crystal_destroyed','First crystal broken'),('dragon_damage','First dragon damage'),('dragon_defeated','Dragon defeated')]:
 x=first(t)
 if x: print(f'{label}: year={x["year"]:.6f} outpost={x.get("outpost",-1)} distance={x.get("distance",0):.3f} amount={x.get("amount",0):.3f}')
cr=[x for x in e if x['type']=='crystal_destroyed']
if cr: print(f'Last crystal broken: year={cr[-1]["year"]:.6f} count={cr[-1].get("count",0)}')
dmg=[x for x in e if x['type']=='dragon_damage']
print('Dragon damage events:',len(dmg))
for n,x in enumerate(dmg,1): print(f'  #{n:03d} year={x["year"]:.6f} damage={x["amount"]:.6f} remaining_hp={x["state"]["dragonHp"]:.6f}')
