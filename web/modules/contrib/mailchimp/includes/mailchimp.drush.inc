<?php

/**
 * @file
 * Mailchimp Module Drush integration.
 */

/**
 * Implements hook_drush_command().
 */
function mailchimp_drush_command() {
  $items = [];

  $items['mailchimp-cron'] = [
    'callback' => '_mailchimp_cron_batch',
    'description' => "Trigger Mailchimp cron task",
    'examples' => [
      'drush mailchimp-cron 5000' => 'Run Mailchimp cron with a batch size of 5000.',
      'drush mailchimp-cron' => 'Run a Mailchimp cron task.',
    ],
  ];

  return $items;
}

/**
 * Callback function to run cron.
 *
 * @int null $temp_batchsize
 */
function _mailchimp_cron_batch($temp_batchsize = NULL) {
  $stored_batchsize = NULL;
  $config = \Drupal::config('mailchimp.settings');
  if (!is_null($temp_batchsize)) {
    $stored_batchsize = $config->get('batch_limit', 100);
    $config->set('batch_limit', $temp_batchsize);
  }
  mailchimp_cron();
  if (!is_null($stored_batchsize)) {
    $config->get('batch_limit', $stored_batchsize);
  }
}
