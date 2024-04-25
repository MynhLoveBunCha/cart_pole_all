clear,clc
load("data_1.mat");
val = squeeze(test_data.signals.values);
val_unbias = val - val(1,:);
[max_val_unbias, idx_max] = max(abs(val_unbias));

t = test_data.time;

val = val(idx_max:end,:);
t = t(idx_max:end,:) - t(idx_max,1);
data_to_simulink = [t,val];
plot(t, val)