clear all; close all;
load fisheriris; % Irisデータセットの読み込み
X=meas'; % 特徴量行列

%% 主成分分析
X_mean=mean(X,2); % 平均
X_center=X-X_mean; % データを中心化
cov_matrix=(X_center*X_center')/(size(X,2)-1); % 共分散行列
[eigenvectors,eigenvalues]=eig(cov_matrix); % 固有ベクトル&固有値
[sort_eigenvalues,sort_index]=sort(diag(eigenvalues),'descend'); % 固有値のソート
sort_eigenvectors=eigenvectors(:,sort_index); % 固有ベクトルの並び替え
principal_eigenvectors=sort_eigenvectors(:,1:2); % 上位2本の固有ベクトルを取得
Z=principal_eigenvectors'*X_center; % サンプルを2次元に射影
% サンプルの2次元散布図をプロット
figure,hold on;
gscatter(Z(1,:),Z(2,:),species,'rgb','ooo');
legend('Location','best');
grid on;

%% 累積寄与率
total_variance=sum(diag(eigenvalues)); % 全体の分散の合計
explain_variance=cumsum(sort_eigenvalues); % 各主成分の分散の累積和
cumulative_contribution_rate=explain_variance/total_variance; % 累積寄与率
% グラフのプロット
figure;
plot(1:4,cumulative_contribution_rate,'bo-','LineWidth',2,'MarkerSize',8);
grid on;