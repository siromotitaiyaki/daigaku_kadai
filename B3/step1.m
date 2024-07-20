clear all; close all; % すべてのグローバル変数/ウィンドを消去
X=load("sample2d.txt"); % sample2d.txtの読み込み
[d,n]=size(X); % Xの次元dとサンプル数nを取得
% サンプルを2次元平面に青点でプロット
figure(1),clf,hold on,plot(X(1,:),X(2,:),"bo");
axis square; % 図を正方に整形

%% 主成分分析
X_mean=mean(X,2); % 平均
X_center=X-X_mean; % データを中心化
cov_matrix=(X_center*X_center')/n; % 共分散行列
[eigenvectors,eigenvalues]=eig(cov_matrix); % 固有ベクトル,固有値
[~,max_index]=max(diag(eigenvalues)); % 最大固有値の抽出
max_eigenvector=eigenvectors(:,max_index); % 固有ベクトルの選択

%% 直線のプロット
xlim([-6,6]); % x軸の範囲
grid on; % 罫線を追加
line_length=7.5; % 長さの調整
line=[X_mean-line_length*max_eigenvector,X_mean+line_length*max_eigenvector];
plot(line(1,:),line(2,:),"g-","LineWidth",1);

%% サンプル分散と最大固有値の比較
Z=max_eigenvector'*X_center; % 正射影
sample_variance=var(Z,1); % サンプル分散
disp(['サンプル分散:',num2str(sample_variance)]);
max_eigenvalue=eigenvalues(max_index,max_index); % 最大固有値
disp(['最大固有値:',num2str(max_eigenvalue)]);