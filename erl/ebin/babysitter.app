{application, babysitter,
 [
  {description, "Babysitter app"},
  {vsn, "0.1"},
  {id, "babysitter"},
  {modules,      []},
  {registered,   []},
  {applications, [kernel, stdlib, sasl]},
  {mod, {babysitter_app, []}},
  {env, [
    {debug, 3}
  ]}
 ]
}.