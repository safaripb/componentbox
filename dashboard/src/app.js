(function () {
  'use strict';

  angular.module('componentBoxApp', [])
    .controller('DashboardController', ['$timeout', '$document', function ($timeout, $document) {
      var vm = this;

      vm.view = 'grid';
      vm.search = '';
      vm.statusFilter = 'all';
      vm.sortOrder = '-capturedAt';
      vm.selectedScan = null;
      vm.toast = '';

      vm.scans = [
        scan(1, '4.7 kΩ', 4700, 'IMG_0842.jpg', 'Today, 10:42 AM', 6, 'identified', 96, ['#f0cf43', '#7b4a99', '#c4493d', '#d6a63b'], 'scan-yellow.svg'),
        scan(2, '1 kΩ', 1000, 'IMG_0841.jpg', 'Today, 10:38 AM', 10, 'identified', 93, ['#724227', '#121212', '#bf3a35', '#d6a63b'], 'scan-blue.svg'),
        scan(3, '', 0, 'IMG_0840.jpg', 'Today, 10:31 AM', 17, 'review', 54, [], 'scan-dark.svg'),
        scan(4, '220 Ω', 220, 'IMG_0839.jpg', 'Yesterday, 4:16 PM', 1090, 'identified', 98, ['#bf3a35', '#bf3a35', '#724227', '#d6a63b'], 'scan-green.svg'),
        scan(5, '10 kΩ', 10000, 'IMG_0838.jpg', 'Yesterday, 3:52 PM', 1114, 'identified', 91, ['#724227', '#121212', '#e58e31', '#d6a63b'], 'scan-purple.svg'),
        scan(6, '330 Ω', 330, 'IMG_0837.jpg', 'Jul 11, 1:24 PM', 2598, 'identified', 88, ['#e58e31', '#e58e31', '#724227', '#d6a63b'], 'scan-red.svg')
      ];

      function scan(id, value, valueNumber, filename, timeLabel, minutesAgo, status, confidence, bands, image) {
        return { id: id, value: value, valueNumber: valueNumber, filename: filename, timeLabel: timeLabel,
          capturedAt: Date.now() - minutesAgo * 60000, status: status, confidence: confidence, bands: bands,
          image: 'assets/scans/' + image };
      }

      vm.filteredScans = function () {
        var term = vm.search.toLowerCase().trim();
        return vm.scans.filter(function (item) {
          var matchesStatus = vm.statusFilter === 'all' || item.status === vm.statusFilter;
          var matchesTerm = !term || (item.value + ' ' + item.filename).toLowerCase().indexOf(term) !== -1;
          return matchesStatus && matchesTerm;
        });
      };

      vm.countByStatus = function (status) {
        return vm.scans.filter(function (item) { return item.status === status; }).length;
      };

      vm.identificationRate = function () {
        return Math.round(vm.countByStatus('identified') / vm.scans.length * 100);
      };

      vm.openScan = function (item) { item.menuOpen = false; vm.selectedScan = item; };
      vm.closeModal = function (event) { if (event.target === event.currentTarget) vm.selectedScan = null; };
      vm.toggleMenu = function (item, event) {
        event.stopPropagation();
        vm.scans.forEach(function (scanItem) { if (scanItem !== item) scanItem.menuOpen = false; });
        item.menuOpen = !item.menuOpen;
      };
      vm.markReviewed = function (item) {
        item.status = 'identified';
        item.value = item.value || 'Check manually';
        item.confidence = item.confidence || 100;
        item.menuOpen = false;
        vm.selectedScan = null;
        showToast('Scan marked as identified');
      };
      vm.removeScan = function (item) {
        vm.scans = vm.scans.filter(function (scanItem) { return scanItem !== item; });
        showToast('Scan removed');
      };
      vm.clearFilters = function () { vm.search = ''; vm.statusFilter = 'all'; };
      vm.startScan = function () { showToast('Camera is ready — place a resistor in view'); };

      function showToast(message) {
        vm.toast = message;
        $timeout(function () { vm.toast = ''; }, 2800);
      }

      $document.on('keydown', function (event) {
        if (event.key === 'Escape') { vm.selectedScan = null; vm.scans.forEach(function (item) { item.menuOpen = false; }); }
        if (event.key === '/' && event.target.tagName !== 'INPUT') {
          event.preventDefault();
          var input = document.querySelector('.search-box input');
          if (input) input.focus();
        }
      });
    }]);
})();
