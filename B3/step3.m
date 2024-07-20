clear all; close all;
load fisheriris; % Irisデータセットの読み込み
X=meas; % 特徴量行列

%% 主成分分析
X_mean=mean(X); % 平均
X_center=X-X_mean; % データを中心化
cov_matrix=cov(X_center); % 共分散行列
[eigenvectors,eigenvalues]=eig(cov_matrix); % 固有ベクトル&固有値
[sort_eigenvalues,sort_index]=sort(diag(eigenvalues),'descend'); % 固有値のソート
sort_eigenvectors=eigenvectors(:,sort_index); % 固有ベクトルの並び替え
r_max=size(sort_eigenvectors,2); % rの最大値
error=zeros(r_max,1); % 事前割り当て
for r=1:r_max % 使用する固有ベクトルの数変更
    U=sort_eigenvectors(:,1:r); % r本の固有ベクトル
    Z=U'*X_center'; % 正射影
    X_reconstruct=(U*Z)'+X_mean; % 再構成
    error(r)=mean(sum((X-X_reconstruct).^2,2)); % 2乗誤差の計算
end

%% 元のサンプルとの2乗誤差の平均
for r=1:r_max
    fprintf('%d:%f\n',r,error(r));
end
% グラフのプロット
figure;
plot(1:r_max,error,'-o');