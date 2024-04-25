xx_saved = xx(:, 1:end-1)';
t_saved = t';
u_saved = u_cl;
headers = ["time (s)", "x (m)", "x_dot (m/s)", "q (rad)", "q_dot (rad/s)", "input (m/s2)"];
data = [t_saved, xx_saved, u_saved];
fileName_data = "data_MPC_with_noise.xlsx";
data_to_saved = array2table(data, "VariableNames", headers);

writetable(data_to_saved, fileName_data);